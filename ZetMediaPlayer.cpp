extern "C" {
#include <stdio.h>
#include <SDL3/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

int main(int argc, char** argv)
{
	AVFormatContext* ptrFormatContext = NULL;

	if (avformat_open_input(&ptrFormatContext, argv[1], NULL, NULL) != 0)
	{
		return -1;
	}

	if (avformat_find_stream_info(ptrFormatContext, NULL) < 0)
	{
		return -1;
	}

	av_dump_format(ptrFormatContext, 0, argv[1], 0);
	return 0;
}