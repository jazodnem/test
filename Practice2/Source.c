#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

int main(void)
{
	SNDFILE *sf;
	SF_INFO info;
	int num_channels;
	int num, num_items;
	int *buffer;
	int frames, sampleRate, channels ;
	int i, j;
	FILE *out;

	/* Open the WAV file. */
	info.format = 0;
	sf = sf_open("D:/Jon/Downloads/file.wav", SFM_READ, &info);
	if (sf == NULL)
	{
		printf("Failed to open the file.\n");
		exit(-1);
	}
	/* Print some of the info, and figure out how much data to read. */
	frames = info.frames;
	sampleRate = info.samplerate;
	channels = info.channels;
	printf("frames=%d\n", frames);
	printf("samplerate=%d\n", sampleRate);
	printf("channels=%d\n", channels);
	num_items = frames*channels;
	printf("num_items=%d\n", num_items);

	/* Allocate space for the data to be read, then read it. */
	buffer = (int *)malloc(num_items*sizeof(int));
	num = sf_read_int(sf, buffer, num_items);
	sf_close(sf);
	printf("Read %d items\n", num);

	/* Write the data to filedata.out. */
	out = fopen("filedata.out", "w");
	for (i = 0; i < num; i += channels)
	{
		for (j = 0; j < channels; ++j)
			fprintf(out, "%d ", buffer[i + j]);
		fprintf(out, "\n");
	}
	fclose(out);
	return 0;
}
