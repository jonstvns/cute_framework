/*
	Cute Framework
	Copyright (C) 2019 Randy Gaul https://randygaul.net

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CUTE_SERVER_H
#define CUTE_SERVER_H

#include <cute_defines.h>
#include <cute_net.h>
#include <cute_crypto.h>

#define CUTE_SERVER_MAX_CLIENTS 256

namespace cute
{

struct server_t;
struct server_event_t;
using client_id_t = uint64_t;

struct server_config_t
{
	int max_clients = 64;
	float client_timeout_time = 20.0f;
	int max_incoming_bytes_per_second = 0;
	int max_outgoing_bytes_per_second = 0;
};

extern CUTE_API server_t* CUTE_CALL server_make(endpoint_t endpoint, const crypto_key_t* public_key, const crypto_key_t* private_key, const server_config_t* config = NULL);
extern CUTE_API void CUTE_CALL server_destroy(server_t* server);

extern CUTE_API void CUTE_CALL server_update(server_t* server, float dt);
extern CUTE_API int CUTE_CALL server_poll_event(server_t* server, server_event_t* event);
extern CUTE_API void CUTE_CALL server_disconnect_client(server_t* server, client_id_t id);
extern CUTE_API void CUTE_CALL server_look_for_and_disconnected_timed_out_clients(server_t* server);
extern CUTE_API void CUTE_CALL server_broadcast_to_all_clients(server_t* server, const void* packet, int size, int reliable);
extern CUTE_API void CUTE_CALL server_broadcast_to_all_but_one_client(server_t* server, const void* packet, int size, client_id_t id, int reliable);
extern CUTE_API void CUTE_CALL server_send_to_client(server_t* server, const void* packet, int size, client_id_t id, int reliable);

enum server_event_type_t
{
	SERVER_EVENT_TYPE_NEW_CONNECTION,
	SERVER_EVENT_TYPE_DISCONNECTED,
	SERVER_EVENT_TYPE_USER_PACKET,
};

struct server_event_t
{
	server_event_type_t type;
	union
	{
		struct
		{
			client_id_t id;
			endpoint_t endpoint;
			crypto_key_t session_key;
		} new_connection;

		struct
		{
			client_id_t id;
		} disconnected;

		struct
		{
			client_id_t id;
			void* data;
			int size;
		} user_packet;
	} u;
};

/*
	Server API - WIP
	server update func
	poll event func (dequeue)
		get user packet from event
		accept new connections via event
	look for timed out clients feature
	disconnect client function
	thread to receive packets from socket
	broadcast funcs - to all, to all but one, to one

	get client data by id
		endpoint
		is loopback

	loopback functions
		send packet
		recieve packet
		client userdata
*/

}

#endif // CUTE_SERVER_H