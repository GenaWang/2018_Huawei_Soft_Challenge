#include"brain.h"
void getbrain(vector<double> &x,vector<double> &xh,int length)
{
	int window_size = length;
	int memory_size = 2;
	int context_length = 5;
	int smoothing = 5;
	Brain brain(window_size, memory_size, context_length, smoothing);
	for(unsigned int i = 0; i < x.size(); i++)
		brain.Perceive(x[i]);

	for(unsigned int i = 0;i < length;i++)
		xh.push_back(brain.Predict());

}
