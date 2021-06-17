
// Defined Varaibles
#define RD64 	32			// Games in the round of 64
#define RD32 	16			// Games in the round of 32
#define RD16 	 8			// Games in the Sweet 16
#define RD8 	 4			// Games in the Elite 8
#define RD4 	 2			// Games in the Final 4
#define RD2 	 1			// Games in the Final 2
#define ROUNDS 	 6			// Number of rounds in the tournament

#define R64RULES 12			// Number of rules for the round of 64

#define MINVALID 16843009	// Smallest number that could be valid

#define G11		1			// 1 seed wins game 1
#define G91		256			// 1 seed wins game 9
#define G171	65536		// 1 seed wins game 17
#define G251	16777216	// 1 seed wins game 25

#define G82		128			// 2 seed wins game 8
#define G162	32768		// 2 seed wins game 16
#define G242	8388608		// 2 seed wins game 24
#define G322	2147483648	// 2 seed wins game 32

#define G63		32			// 3 seed wins game 6
#define G143	8192		// 3 seed wins game 14
#define G223	2097152		// 3 seed wins game 22
#define G303	536870912	// 3 seed wins game 30 

#define G44		8			// 4 seed wins game 4
#define G124	2048		// 4 seed wins game 12
#define G204	524288		// 4 seed wins game 20
#define G284	134217728	// 4 seed wins game 28 

#define G35		4			// 5 seed wins game 3
#define G115	1024		// 5 seed wins game 11
#define G195	262144		// 5 seed wins game 19
#define G275	67108864	// 5 seed wins game 27

#define G56		16			// 6 seed wins game 5
#define G136	4096		// 6 seed wins game 13
#define G216	1048576		// 6 seed wins game 21
#define G296	268435456	// 6 seed wins game 29

#define G77		64			// 7 seed wins game 7
#define G157	16384		// 7 seed wins game 15
#define G237	4194304		// 7 seed wins game 23
#define G317	1073741824	// 7 seed wins game 31

#define G28		2			// 8 seed wins game 2
#define G108	512			// 8 seed wins game 10
#define G188	131072		// 8 seed wins game 18
#define G268	33554432	// 8 seed wins game 26



// Global Variables
struct  bracket
{
	int rounds;
	unsigned long round64seed;
	unsigned int round32seed;
	int round16seed;
	int round8seed;
	int round4seed;
	int round2seed;
	int rd64[RD64];
	int rd32[RD32];
	int rd16[RD16];
	int rd8[RD8];
	int rd4[RD4];
	int rd2[RD2];
};

// Functions
/*---------------------------------------------------------------------------*/
// convert seed numbers to arrays
void convert_seeds(unsigned long rd64, unsigned int rd32, int rd16, int rd8, int rd4, int rd2);

// clear the current sample
void clear_sample(void);

// populates the current sample with generated values
void populate_sample(unsigned long round_seeds[]);

// prints the current sample
void print_sample(void);

// checks if current seed is valid
int is_valid(unsigned long seed, int round);

// functions that contain rules for each individual round
int rd64_isvalid(unsigned long seed);
int rd32_isvalid(unsigned int seed);
int rd16_isvalid(int seed);
int rd8_isvalid(int seed);
int rd4_isvalid(int seed);
int rd2_isvalid(int seed);

// rule checks
/*---------------------------------------------------------------------------*/
int call_rule(int rule, unsigned long seed);
// round of 64
int all_ones(unsigned long seed);	// all 1 seeds win
int all_twos(unsigned long seed);	// all 2 seeds win
int all_threes(unsigned long seed);	// all 3 seeds win
int three_twelves(unsigned long seed);	// max of 3 12 seeds win
int two_thirteens(unsigned long seed);	// max of 2 13 seeds win
int max_upsets(unsigned long seed);	// max of 10 total upsets
int four_max_twelve_thirteen(unsigned long seed);	// 12 and 13 seeds combine for 4 upsets or less
int three_tens(unsigned long seed);		// no more than 3 10 seeds win
int three_elevens(unsigned long seed);	// no more than 3 11 seeds win
int six_in_quad(unsigned long seed);	// max of 5 upsets per quadrant
int max_one_fifteen(unsigned long seed);	// max of 1 15 seed win
int max_one_fourteen(unsigned long seed);	// max of 1 14 seed win
int min_upsets(unsigned long seed);	// min of 3 total upsets
int five_max_eleven_twelve(unsigned long seed);	// 11 and 12 seeds combine for 5 upsets or less
int five_max_ten_eleven(unsigned long seed);	// 10 and 11 seeds combine for 5 upsets or less
int four_max_ten_twelve(unsigned long seed);		// 10 and 12 seeds combine for 4 upsets or less

// look for minimum 1 9 seed, min 1 10 seed, maybe min 1 11, maybe max 3 9's