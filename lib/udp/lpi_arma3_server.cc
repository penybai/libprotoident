/*
 *
 * Copyright (c) 2011-2016 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libprotoident.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"

static inline bool match_arma3_server_payload(uint32_t payload, uint32_t len) {

        uint32_t replen;

        if (len == 0)
                return true;

        replen = (payload & 0xffff);
        if (replen != len)
                return false;

        if (MATCH(payload, ANY, ANY, 0xe2, 0x16))
                return true;
        if (MATCH(payload, ANY, ANY, 0x60, 0xcf))
                return true;


        return false;


}

static inline bool match_arma_port_range(lpi_data_t *data) {

        if (data->server_port >= 2300 && data->server_port <= 2400)
                return true;
        if (data->client_port >= 2300 && data->client_port <= 2400)
                return true;

        return false;
}

static inline bool match_arma3_server(lpi_data_t *data, lpi_module_t *mod UNUSED) {

        if (match_arma3_server_payload(data->payload[0], data->payload_len[0])) {
                if (match_arma3_server_payload(data->payload[1], data->payload_len[1]))
                        return true;
        }

	return false;
}

static lpi_module_t lpi_arma3_server = {
	LPI_PROTO_UDP_ARMA3_SERVER,
	LPI_CATEGORY_GAMING,
	"ARMA3Server",
	4,
	match_arma3_server
};

void register_arma3_server(LPIModuleMap *mod_map) {
	register_protocol(&lpi_arma3_server, mod_map);
}

