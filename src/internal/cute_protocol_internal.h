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

#ifndef CUTE_PROTOCOL_INTERNAL_H
#define CUTE_PROTOCOL_INTERNAL_H

#include <cute_protocol.h>

namespace cute
{

struct packet_queue_t
{
	int count = 0;
	int index0 = 0;
	int index1 = 0;
	packet_type_t types[CUTE_PACKET_QUEUE_MAX_ENTRIES];
	void* packets[CUTE_PACKET_QUEUE_MAX_ENTRIES];
};

extern CUTE_API void CUTE_CALL packet_queue_init(packet_queue_t* q);
extern CUTE_API int CUTE_CALL packet_queue_push(packet_queue_t* q, void* packet, packet_type_t type);
extern CUTE_API int CUTE_CALL packet_queue_pop(packet_queue_t* q, void** packet, packet_type_t* type);

struct replay_buffer_t
{
	uint64_t max;
	uint64_t entries[CUTE_REPLAY_BUFFER_SIZE];
};

extern CUTE_API void CUTE_CALL replay_buffer_init(replay_buffer_t* buffer);
extern CUTE_API int CUTE_CALL replay_buffer_cull_duplicate(replay_buffer_t* buffer, uint64_t sequence);
extern CUTE_API void CUTE_CALL replay_buffer_update(replay_buffer_t* buffer, uint64_t sequence);

struct packet_allocator_t;

extern CUTE_API packet_allocator_t* CUTE_CALL packet_allocator_make(void* user_allocator_context = NULL);
extern CUTE_API void CUTE_CALL packet_allocator_destroy(packet_allocator_t* packet_allocator);
extern CUTE_API void* CUTE_CALL packet_allocator_alloc(packet_allocator_t* packet_allocator, packet_type_t type);
extern CUTE_API void CUTE_CALL packet_allocator_free(packet_allocator_t* packet_allocator, packet_type_t type, void* packet);

int packet_write(void* packet_ptr, packet_type_t packet_type, uint8_t* buffer, uint64_t game_id, uint64_t sequence, const crypto_key_t* key);
void* packet_open(packet_allocator_t* pa, replay_buffer_t* nonce_buffer, uint64_t game_id, uint64_t timestamp, uint8_t* buffer, int size, uint64_t sequence_offset, const crypto_key_t* key, int is_server, packet_type_t* packet_type);



struct packet_decrypted_connect_token_t
{
	uint64_t expire_timestamp;
	uint64_t client_id;
	uint64_t sequence_offset;
	crypto_key_t key;
	uint16_t endpoint_count;
	endpoint_t endpoints[CUTE_CONNECT_TOKEN_SERVER_COUNT_MAX];
	uint8_t user_data[CUTE_CONNECT_TOKEN_USER_DATA_SIZE];
};

struct packet_encrypted_connect_token_t
{
	uint64_t expiration_timestamp;
	uint8_t nonce[CUTE_CONNECT_TOKEN_NONCE_SIZE];
	uint8_t secret_data[CUTE_CONNECT_TOKEN_SECRET_SECTION_SIZE];
};

struct packet_connection_accepted_t
{
	int client_number;
	int max_clients;
};

struct packet_connection_denied_t
{
	uint8_t packet_type;
};

struct packet_keepalive_t
{
	uint8_t packet_type;
};

struct packet_disconnect_t
{
	uint8_t packet_type;
};

struct packet_challenge_t
{
	uint64_t nonce;
	uint8_t challenge_data[CUTE_CHALLENGE_DATA_SIZE];
};

struct packet_userdata_t
{
	int size;
	uint8_t data[CUTE_PACKET_PAYLOAD_MAX];
};

struct connect_token_client_data_t
{
	uint64_t application_id;
	uint64_t expiration_timestamp;
	uint64_t creation_timestamp;
	crypto_key_t client_to_server_key;
	crypto_key_t server_to_client_key;
	uint32_t handshake_timeout;
	uint16_t endpoint_count;
	endpoint_t endpoints[CUTE_CONNECT_TOKEN_SERVER_COUNT_MAX];
};

extern CUTE_API uint8_t* CUTE_CALL connect_token_process_client_data(uint8_t* buffer, connect_token_client_data_t* token);

struct connect_token_t
{
	uint8_t nonce[CUTE_CONNECT_TOKEN_NONCE_SIZE];
	uint8_t secret_data_and_hmac[CUTE_CONNECT_TOKEN_SECRET_SECTION_SIZE + CUTE_CRYPTO_HMAC_BYTES];
};

}

#endif // CUTE_PROTOCOL_INTERNAL_H
