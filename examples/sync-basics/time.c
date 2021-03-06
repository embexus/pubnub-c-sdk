#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <json.h>

#include "pubnub.h"
#include "pubnub-sync.h"

int
main(void)
{
	struct pubnub_sync *sync = pubnub_sync_init();
	struct pubnub *p = pubnub_init(
			/* publish_key */ "demo",
			/* subscribe_key */ "demo",
			/* pubnub_callbacks */ &pubnub_sync_callbacks,
			/* pubnub_callbacks data */ sync);
	json_object *msg;


	pubnub_time(
			/* struct pubnub */ p,
			/* default timeout */ -1,
			/* callback; sync needs NULL! */ NULL,
			/* callback data */ NULL);

	if (pubnub_sync_last_result(sync) != PNR_OK)
		return EXIT_FAILURE;

	msg = pubnub_sync_last_response(sync);
	int64_t ts = json_object_get_int64(msg);
	printf("%"PRId64"\n", ts);
	json_object_put(msg);


	pubnub_done(p);
	return EXIT_SUCCESS;
}
