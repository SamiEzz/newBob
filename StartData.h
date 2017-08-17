#ifndef H_GLOBAL
#define H_GLOBAL
struct BUF{
	int WIDTH;
	int HEIGHT;
	unsigned char *BUFFER;
};

struct CAL{
	float X_START;
	float Y_START;
	float DX;
	float DY;
	int LENGHT_BEAM;
	int LENGHT_BALL;
	int THRESHOLD;
};

struct POS{
	int X;
	int Y;
	bool DETECTIONOK;
};

#endif







