#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>


struct MediaPlayerCodec
{
	const AVCodec* codec = NULL;
	AVFormatContext* formatContext = NULL;
	AVCodecParameters* codecParameters = NULL;
	AVCodecContext* codecContext = NULL;
	int videoStream = -1;
};

struct MediaPlayerFrame
{
	AVFrame* frame = NULL;
	AVFrame* frameRGB = NULL;
	uint8_t* buffer = NULL;
	int numBytes;
};