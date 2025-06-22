/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#include "lwip/netif.h"
#include "lwip/ip_addr.h"

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("failed to initialise\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_MIXED_PSK, 10000)) {
        printf("failed to connect\n");
        return 1;
    }

    sleep_ms(5000);

    struct netif *netif = &cyw43_state.netif[0];
    printf("Connected with IP: %s\n", ipaddr_ntoa(&netif->ip_addr));

    cyw43_arch_deinit();
   return 0;
}
