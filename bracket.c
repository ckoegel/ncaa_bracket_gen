#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bracket.h"

unsigned long current_sample[ROUNDS] = {};
struct bracket sample;
long num_brackets = 0;

int main(void) {
	
	for (unsigned long r64 = MINVALID; r64 < pow(2,RD64); r64+=2) {	//pow(2,RD64)
		//printf("%ld\n",r64);
		if (is_valid(r64, RD64)) {
			//current_sample[0] = r64;
			//populate_sample(current_sample);
			num_brackets++;
			//print_sample();
		}
		
	}
	printf("Number of Brackets: %ld\n", num_brackets);
	FILE *f = fopen("bracket.txt", "a");
	fprintf(f, "Number of Brackets: %ld\n", num_brackets);
	fclose(f);
    return 0;
}
	
void convert_seeds(unsigned long rd64, unsigned int rd32, int rd16, int rd8, int rd4, int rd2) {

	for (int j = RD64; j > 0; j--){
		sample.rd64[RD64 - j] = rd64 & 1;
		rd64 = rd64 >> 1;
	}
	for (int j = RD32; j > 0; j--){
		sample.rd32[RD32 - j] = rd32 & 1;
		rd32 = rd32 >> 1;
	}
	for (int j = RD16; j > 0; j--){
		sample.rd16[RD16 - j] = rd16 & 1;
		rd16 = rd16 >> 1;
	}
	for (int j = RD8; j > 0; j--){
		sample.rd8[RD8 - j] = rd8 & 1;
		rd8 = rd8 >> 1;
	}
	for (int j = RD4; j > 0; j--){
		sample.rd4[RD4 - j] = rd4 & 1;
		rd4 = rd4 >> 1;
	}
	for (int j = RD2; j > 0; j--){
		sample.rd2[RD2 - j] = rd2 & 1;
		rd2 = rd2 >> 1;
	}
}

void clear_sample(void) {
	memset(sample.rd64, 0, RD64*sizeof(unsigned long));
	memset(sample.rd32, 0, RD32*sizeof(unsigned int));
	memset(sample.rd16, 0, RD16*sizeof(int));
	memset(sample.rd8, 0, RD8*sizeof(int));
	memset(sample.rd4, 0, RD4*sizeof(int));
	memset(sample.rd2, 0, RD2*sizeof(int));
	sample.round64seed = 0;
	sample.round32seed = 0;
	sample.round16seed = 0;
	sample.round8seed = 0;
	sample.round4seed = 0;
	sample.round2seed = 0;
}

void populate_sample(unsigned long round_seeds[]) {
	sample.round64seed = round_seeds[0];
	sample.round32seed = round_seeds[1];
	sample.round16seed = round_seeds[2];
	sample.round8seed = round_seeds[3];
	sample.round4seed = round_seeds[4];
	sample.round2seed = round_seeds[5];
	convert_seeds(sample.round64seed, sample.round32seed, sample.round16seed, sample.round8seed, sample.round4seed, sample.round2seed);
}

void print_sample(void) {
	FILE *f = fopen("bracket.txt", "a");
	fprintf(f,"Round of 64  - ");
	for (int j = 0; j < RD64; j++) {
		fprintf(f, "%d", sample.rd64[j]);
		if ((j + 1) % 8 == 0) {fprintf(f, " ");}
	}
	fprintf(f,"\n");
	fprintf(f, "Round of 32  -   ");
	for (int j = 0; j < RD32; j++) {
		fprintf(f, "%d", sample.rd32[j]);
		if ((j + 1) % 4 == 0) {fprintf(f, "     ");}
	}
	fprintf(f,"\n");
	fprintf(f, "Sweet 16     -    ");
	for (int j = 0; j < RD16; j++) {
		fprintf(f, "%d", sample.rd16[j]);
		if ((j + 1) % 2 == 0) {fprintf(f, "       ");}
	}
	fprintf(f,"\n");
	fprintf(f, "Elite 8      -     ");
	for (int j = 0; j < RD8; j++) {
		fprintf(f, "%d        ", sample.rd8[j]);
	}
	fprintf(f,"\n");
	fprintf(f, "Final Four   -              ");
	for (int j = 0; j < RD4; j++) {
		fprintf(f, "%d        ", sample.rd4[j]);
	}
	fprintf(f,"\n");
	fprintf(f, "Championship -                  ");
	for (int j = 0; j < RD2; j++) {
		fprintf(f, "%d", sample.rd2[j]);
	}
	fprintf(f,"\n");
	fprintf(f,"\n");
	fclose(f);
}

int is_valid(unsigned long seed, int round) {
	switch (round)
	{
	case RD64:
		if (rd64_isvalid(seed)) {
			return 1;
		}
		break;

	case RD32:
		if (rd32_isvalid(seed)) {
			return 1;
		}
		break;
	case RD16:
		if (rd16_isvalid(seed)) {
			return 1;
		}
		break;
	case RD8:
		if (rd8_isvalid(seed)) {
			return 1;
		}
		break;
	case RD4:
		if (rd4_isvalid(seed)) {
			return 1;
		}
		break;
	case RD2:
		if (rd2_isvalid(seed)) {
			return 1;
		}
		break;
	default:
		return 0;
		break;
	} 
	return 0;
}

int rd64_isvalid(unsigned long seed) {

	return all_ones(seed) &&	// comment out rules not used
	 	all_twos(seed) &&
		all_threes(seed) &&
		three_twelves(seed) &&
	   	two_thirteens(seed) &&
	    max_upsets(seed) &&
		four_max_twelve_thirteen(seed) &&
		three_tens(seed) &&
		three_elevens(seed) &&
		six_in_quad(seed) &&
		//max_one_fifteen(seed) &&
		//max_one_fourteen(seed) &&
		min_upsets(seed) &&
		five_max_eleven_twelve(seed) &&
		five_max_ten_eleven(seed) &&
		four_max_ten_twelve(seed);

}

int rd32_isvalid(unsigned int seed) {
	return 1;
}

int rd16_isvalid(int seed) {
	return 1;
}

int rd8_isvalid(int seed) {
	return 1;
}

int rd4_isvalid(int seed) {
	return 1;
}

int rd2_isvalid(int seed) {
	return 1;
}

// Round of 64 Rules
int all_ones(unsigned long seed) { // Make sure all 1 seeds win in the first round
	return (seed & G11) && (seed & G91) && (seed & G171) && (seed & G251);
}

int all_twos(unsigned long seed) { // Make sure all 2 seeds win in the first round
	return (seed & G82) && (seed & G162) && (seed & G242) && (seed & G322);
}

int all_threes(unsigned long seed) { // Make sure all 3 seeds win in the first round
	return (seed & G63) && (seed & G143) && (seed & G223) && (seed & G303);
}

int three_twelves(unsigned long seed) { // Make sure no more than 3 12 seeds win in the first round
	int sum = 0;
	if (seed & G35) {sum++;}
	if (seed & G115) {sum++;}
	if (seed & G195) {sum++;}
	if (seed & G275) {sum++;}
	return  sum >= 1;
}

int two_thirteens(unsigned long seed) { // Make sure no more than 2 13 seeds win in the first round
	int sum = 0;
	if (seed & G44) {sum++;}
	if (seed & G124) {sum++;}
	if (seed & G204) {sum++;}
	if (seed & G284) {sum++;}
	return  sum >= 2;
}

int max_upsets(unsigned long seed) { // Make sure there are no more than 10 upsets in the first round
	int sum = 0;
	while (seed) {
		sum += seed & 1;
		seed = seed >> 1;
	}
	return sum >= 22;
}

int four_max_twelve_thirteen(unsigned long seed) { // Make sure the 12 and 13 seeds combine for a max of 4 upsets
	int sum = 0;
	if (seed & G35) {sum++;}
	if (seed & G115) {sum++;}
	if (seed & G195) {sum++;}
	if (seed & G275) {sum++;}
	if (seed & G44) {sum++;}
	if (seed & G124) {sum++;}
	if (seed & G204) {sum++;}
	if (seed & G284) {sum++;}
	return sum >= 4;
}

int three_tens(unsigned long seed) { // Make sure no more than 3 10 seeds win in the first round
	int sum = 0;
	if (seed & G77) {sum++;}
	if (seed & G157) {sum++;}
	if (seed & G237) {sum++;}
	if (seed & G317) {sum++;}
	return  sum >= 1;
}

int three_elevens(unsigned long seed) { // Make sure no more than 3 11 seeds win in the first round
	int sum = 0;
	if (seed & G56) {sum++;}
	if (seed & G136) {sum++;}
	if (seed & G216) {sum++;}
	if (seed & G296) {sum++;}
	return  sum >= 1;
}

int six_in_quad(unsigned long seed) { // Make sure there are not more than 5 upsets in a single quadrant
	int sumQ1 = 0, sumQ2 = 0, sumQ3 = 0, sumQ4 = 0;
	if (seed & G11) {sumQ1++;}
	if (seed & G28) {sumQ1++;}
	if (seed & G35) {sumQ1++;}
	if (seed & G44) {sumQ1++;}
	if (seed & G56) {sumQ1++;}
	if (seed & G63) {sumQ1++;}
	if (seed & G77) {sumQ1++;}
	if (seed & G82) {sumQ1++;}

	if (seed & G91) {sumQ2++;}
	if (seed & G108) {sumQ2++;}
	if (seed & G115) {sumQ2++;}
	if (seed & G124) {sumQ2++;}
	if (seed & G136) {sumQ2++;}
	if (seed & G143) {sumQ2++;}
	if (seed & G157) {sumQ2++;}
	if (seed & G162) {sumQ2++;}

	if (seed & G171) {sumQ3++;}
	if (seed & G188) {sumQ3++;}
	if (seed & G195) {sumQ3++;}
	if (seed & G204) {sumQ3++;}
	if (seed & G216) {sumQ3++;}
	if (seed & G223) {sumQ3++;}
	if (seed & G237) {sumQ3++;}
	if (seed & G242) {sumQ3++;}

	if (seed & G251) {sumQ4++;}
	if (seed & G268) {sumQ4++;}
	if (seed & G275) {sumQ4++;}
	if (seed & G284) {sumQ4++;}
	if (seed & G296) {sumQ4++;}
	if (seed & G303) {sumQ4++;}
	if (seed & G317) {sumQ4++;}
	if (seed & G322) {sumQ4++;}

	return (sumQ1 > 2) && (sumQ2 > 2) && (sumQ3 > 2) && (sumQ4 > 2);
}

int max_one_fifteen(unsigned long seed) { // Make sure a max of 1 15 seed wins in the first round
	int sum = 0;
	if (seed & G82) {sum++;}
	if (seed & G162) {sum++;}
	if (seed & G242) {sum++;}
	if (seed & G322) {sum++;}
	return  sum >= 3;
}

int max_one_fourteen(unsigned long seed) { // Make sure a max of 1 14 seed wins in the first round
	int sum = 0;
	if (seed & G63) {sum++;}
	if (seed & G143) {sum++;}
	if (seed & G223) {sum++;}
	if (seed & G303) {sum++;}
	return  sum >= 3;
}

int min_upsets(unsigned long seed) { // Make sure there is a minimum of 5 upsets in the first round
	int sum = 0;
	while (seed) {
		sum += seed & 1;
		seed = seed >> 1;
	}
	return sum <= 27;
}

int five_max_eleven_twelve(unsigned long seed) {
	int sum = 0;
	if (seed & G35) {sum++;}
	if (seed & G115) {sum++;}
	if (seed & G195) {sum++;}
	if (seed & G275) {sum++;}
	if (seed & G56) {sum++;}
	if (seed & G136) {sum++;}
	if (seed & G216) {sum++;}
	if (seed & G296) {sum++;}
	return sum >= 3;
}

int five_max_ten_eleven(unsigned long seed) {
	int sum = 0;
	if (seed & G77) {sum++;}
	if (seed & G157) {sum++;}
	if (seed & G237) {sum++;}
	if (seed & G317) {sum++;}
	if (seed & G56) {sum++;}
	if (seed & G136) {sum++;}
	if (seed & G216) {sum++;}
	if (seed & G296) {sum++;}
	return sum >= 3;
}

int four_max_ten_twelve(unsigned long seed) {
	int sum = 0;
	if (seed & G77) {sum++;}
	if (seed & G157) {sum++;}
	if (seed & G237) {sum++;}
	if (seed & G317) {sum++;}
	if (seed & G35) {sum++;}
	if (seed & G115) {sum++;}
	if (seed & G195) {sum++;}
	if (seed & G275) {sum++;}
	return sum >= 4;
}