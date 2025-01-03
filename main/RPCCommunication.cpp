#include "esp_log.h"
#include "Gearbox.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "RPCClient.h"
#include "RPCCommunication.h"
#include "Gearbox.h"

static const char *TAG = "RPCCOMMUNICATION";

void RPCCommunication::rpc_communication_task(void *args) {
    RPCClient::init();

    struct sockaddr_in dest_addr_main;
    dest_addr_main.sin_addr.s_addr = inet_addr("192.168.1.101");
    dest_addr_main.sin_family = AF_INET;
    dest_addr_main.sin_port = htons(90);

    /*

    struct sockaddr_in dest_addr_accelerator;
    dest_addr_accelerator.sin_addr.s_addr = inet_addr("192.168.X.X");
    dest_addr_accelerator.sin_family = AF_INET;
    dest_addr_accelerator.sin_port = htons(90);

    struct sockaddr_in dest_addr_relay;
    dest_addr_relay.sin_addr.s_addr = inet_addr("192.168.X.X");
    dest_addr_relay.sin_family = AF_INET;
    dest_addr_relay.sin_port = htons(90);

    */

    while (true) {
        ESP_LOGI(TAG, "virtual curr gear %d", get_current_gear());
        RPCClient::send_request("set_gearbox_state", (int32_t)get_gearbox_ready(), (int32_t)get_current_gear(), dest_addr_main);
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void RPCCommunication::init() {
    xTaskCreate(rpc_communication_task, "rpc com task", 8192, NULL, 24, NULL);
}
