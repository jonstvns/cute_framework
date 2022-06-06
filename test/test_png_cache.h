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

#include <cute.h>
using namespace cute;

CUTE_TEST_CASE(test_png_cache, "Test all functions of the png caching API.");
int test_png_cache()
{
	cf_file_system_init(NULL);
	cf_file_system_mount(cf_file_system_get_base_dir(), "");

	cf_png_cache_t* cache = cf_png_cache_make();

	cf_png_t white;
	cf_png_t black;
	cf_error_t err = cf_png_cache_load(cache, "test_data/white_pixel.png", &white);
	CUTE_TEST_ASSERT(!err.is_error());
	err = cf_png_cache_load(cache, "test_data/black_pixel.png", &black);
	CUTE_TEST_ASSERT(!err.is_error());

	const cf_animation_t* blink_anim = cf_png_cache_make_animation(cache, "blink", { white, black }, { 0.5f, 0.5f });
	const cf_animation_t* white_anim = cf_png_cache_make_animation(cache, "white", { white }, { 1.0f });
	const cf_animation_t* black_anim = cf_png_cache_make_animation(cache, "black", { black }, { 1.0f });
	cf_png_cache_make_animation_table(cache, "blink", { blink_anim, white_anim, black_anim } );
	cf_sprite_t sprite = cf_png_cache_make_sprite(cache, "blink");

	sprite.play("blink");
	CUTE_TEST_CHECK_POINTER(sprite.animations);
	CUTE_TEST_ASSERT(sprite.frame_index == 0);

	sprite.update(0.5f);
	CUTE_TEST_ASSERT(sprite.frame_index == 1);

	cf_png_cache_destroy(cache);

	cf_file_system_destroy();

	return 0;
}

