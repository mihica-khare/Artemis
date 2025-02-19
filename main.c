#include <coap3/coap.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>

#define SERVER_IP "192.168.1.100"
#define SERVER_PORT 5683
#define SENSOR_PATH "sensor"
#define SEND_INTERVAL 1  // Send data every 1 second

coap_context_t *ctx = NULL;
coap_session_t *session = NULL;

float read_temperature() {
    // Dummy function - Replace with actual sensor read logic
    return 23.5 + (rand() % 100) / 100.0;
}

void send_sensor_data() {
    coap_address_t dst;
    coap_address_init(&dst);
    dst.addr.sin.sin_family = AF_INET;
    dst.addr.sin.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &dst.addr.sin.sin_addr);

    ctx = coap_new_context(NULL);
    if (!ctx) {
        fprintf(stderr, "Failed to create CoAP context\n");
        return;
    }

    session = coap_new_client_session(ctx, NULL, &dst, COAP_PROTO_UDP);
    if (!session) {
        fprintf(stderr, "Failed to create CoAP session\n");
        coap_free_context(ctx);
        return;
    }

    while (1) {
        coap_pdu_t *pdu = coap_pdu_init(COAP_MESSAGE_CON, 
                                        COAP_REQUEST_CODE_POST, 
                                        coap_new_message_id(session), 
                                        coap_session_max_pdu_size(session));
        if (!pdu) {
            fprintf(stderr, "Failed to create PDU\n");
            break;
        }

        coap_add_option(pdu, COAP_OPTION_URI_PATH, strlen(SENSOR_PATH), (const uint8_t *)SENSOR_PATH);
        
        char payload[32];
        float temp = read_temperature();
        snprintf(payload, sizeof(payload), "temp=%.2f", temp);
        coap_add_data(pdu, strlen(payload), (uint8_t *)payload);

        if (coap_send(session, pdu) == COAP_INVALID_TID) {
            fprintf(stderr, "Failed to send CoAP message\n");
            coap_delete_pdu(pdu);
            break;
        }

        printf("Sent: %s\n", payload);
        sleep(SEND_INTERVAL);
    }
}

void cleanup() {
    if (session) coap_session_release(session);
    if (ctx) coap_free_context(ctx);
}

void handle_signal(int signal) {
    printf("Terminating...\n");
    cleanup();
    exit(0);
}

int main() {
    signal(SIGINT, handle_signal);  // Handle Ctrl+C for cleanup
    send_sensor_data();
    cleanup();
    return 0;
}

