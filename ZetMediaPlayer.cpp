extern "C" {
#include "ZetMediaPlayer.h"
}

int main(int argc, char** argv)
{
	MediaPlayerCodec codec;
	MediaPlayerFrame frame;

	if (avformat_open_input(&codec.formatContext, argv[1], NULL, NULL) != 0)
	{
		return -1;
	}

	if (avformat_find_stream_info(codec.formatContext, NULL) < 0)
	{
		return -1;
	}

	for (int i = 0; i < codec.formatContext->nb_streams; ++i)
	{		
		if (codec.formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			codec.videoStream = i;
			break;
		}
	}

	if (codec.videoStream == -1)
	{
		return -1;
	}

	codec.codecParameters = codec.formatContext->streams[codec.videoStream]->codecpar;
	codec.codec = avcodec_find_decoder(codec.codecParameters->codec_id);

	if (codec.codec == NULL)
	{
		fprintf(stderr, "Unsupported codec\n");
		return -1;
	}

	codec.codecContext = avcodec_alloc_context3(codec.codec);
	if (codec.codecContext == NULL)
	{
		fprintf(stderr, "Failed to allocate codec context\n");
		return -1;
	}

	if (avcodec_open2(codec.codecContext, codec.codec, NULL) < 0)
	{
		fprintf(stderr, "Failed to open codec\n");
		return -1;
	}

	frame.frame = av_frame_alloc();


	av_dump_format(codec.formatContext, 0, argv[1], 0);
	return 0;
}