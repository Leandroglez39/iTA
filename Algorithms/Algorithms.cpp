

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <string>
#include <iostream>
#include <filesystem>
#include <windows.h>
#include "edlib.h"
#include "Nj.h"
#include "Tools.h"
#include "_editdistance.h"
#include <omp.h>
#include "Input.h"
#include "mstar.h"
#include "Refine.h"



using namespace std;


void printAlignment(const char* query, const char* target,
	const unsigned char* alignment, const int alignmentLength,
	const int position, const EdlibAlignMode modeCode);

long long foo(int64_t* a, int64_t* b, size_t i, size_t j);

struct tup
{
	int64_t* h;
	int64_t* q;

	tup(int64_t* h, int64_t* q)
	{
		this->h = h;
		this->q = q;
	}
};

int main()
{


	
	vector<double> times;

	// read all files names in a .txt file

	vector<string> lines;
	
	// Set the number of iterations we want to do for each file
	// The number of iterations is the number of times we want to run the algorithm for each file
	// For example, if we have 50 files and we want to run the algorithm 50 times for each file, we will have 50*50 = 2500 iterations
	// The times vector will store the time it takes to run the algorithm for each iteration
	int iterations = 5;


	// Main loop for the number of iterations we want to do
	for (int j = 0; j < iterations; j++)
	{

		// create a new instance of the NJ class
		auto gt = NJ();


		// Vector to store the seuqences
		vector<string> sequences;
		// Vector to store the profiles
		vector<vector<string>> profiles;
		// Vector to store the sorted sequences
		vector<string> sequences_sort;
		// dictionary to store the the correlation between the unique characters and the index was used
		map<char, pair<int, vector<int>>> dic;


		

		// Path to the data folder
		string data_path = "../data/";

		// Name of the file, without the extension
		// If the file isn't in the same folder as the executable, you need to specify the path
		string name = "12";

		// Extensions of the input files
		string txt = ".txt";
		// Extension of the output file
		string fasta = ".fasta";

		auto start = clock();

		// Read the file and store the sequences in the sequences vector
		// The sequences vector will store the sequences in the same order as they are in the file
		gt.init_data(sequences, profiles, data_path + name + txt);

		vector<int> check_seq(sequences.size());

		// Initialize the clusters
		gt.init_clusters(sequences.size());

		std::cout << "Init Data OK en: ";
		std::cout << std::fixed << std::setprecision(5) << static_cast<double>((clock() - start)) * 1000 / CLOCKS_PER_SEC << " milliseconds." << std::endl;


		// Vector to store the pair alignments
		vector<pair<string, string>> pair_alignments(sequences.size());
		// Vector to store the multiple alignment
		vector<string> mul_align(sequences.size());
		// Vector to store the multiple alignment
		vector<string> parser_alig(sequences.size());


		int piv = 0;
		start = clock();

		auto ti = clock();

		// Calculate the distance matrix
		build_distance_matrix(sequences, piv);

		std::cout << "Distance Matrix en: ";
		std::cout << static_cast<double>((clock() - start) * 1000) / CLOCKS_PER_SEC << " milliseconds." << endl;

		start = clock();

		// Calculate the pair alignments
		pair_alignment(sequences, pair_alignments, piv);

		std::cout << "PSA en: ";
		std::cout << static_cast<double>((clock() - start) * 1000) / CLOCKS_PER_SEC << " milliseconds." << endl;

		start = clock();

		// Calculate the multiple alignment
		msa(pair_alignments, mul_align, piv);


		std::cout << "MSA en: ";
		std::cout << static_cast<double>((clock() - start) * 1000) / CLOCKS_PER_SEC << " milliseconds." << endl;

		start = clock();

		cout << mul_align[0].size() << endl;

		// Refine the multiple alignment fir step, erase columns with all elements equal to '-'
		erase_gaps(mul_align);

		std::cout << "Refinamiento en: ";
		std::cout << static_cast<double>((clock() - start) * 1000) / CLOCKS_PER_SEC << " milliseconds." << endl;

		start = clock();

		// Refine the multiple alignment second step, block shift refinement
		block_shift_refinement(mul_align);

		// Refine the multiple alignment third step, erase columns with all elements equal to '-'
		erase_gaps(mul_align);


		std::cout << "Block Shift en: ";
		std::cout << static_cast<double>((clock() - start) * 1000) / CLOCKS_PER_SEC << " milliseconds." << endl;

		std::cout << "Tiempo total en: ";
		std::cout << static_cast<double>(clock() - ti) * 1000 / CLOCKS_PER_SEC << " milliseconds." << endl;

		times.push_back(static_cast<double>(clock() - ti) * 1000 / CLOCKS_PER_SEC);


		cout << mul_align[0].size() << endl;
		start = clock();
		
		// Save the multiple alignment in a file

		// Output folder path
		string output_path = "../outputs/";

		input::save_alignment(output_path + name + fasta, mul_align);

		std::cout << "Save en: ";
		std::cout << static_cast<double>(clock() - start) * 1000 / CLOCKS_PER_SEC << " milliseconds." << endl;




	}




	// Calculate de average time into the times vector
	double sum = 0;
	for (int i = 0; i < times.size(); i++)
	{
		sum += times[i];
	}
	double average = sum / times.size();
	std::cout << "Average time: " << average << std::endl;



	std::cout << " OK";
}
void printAlignment(const char* query, const char* target,
	const unsigned char* alignment, const int alignmentLength,
	const int position, const EdlibAlignMode modeCode) {
	int tIdx = -1;
	int qIdx = -1;
	if (modeCode == EDLIB_MODE_HW) {
		tIdx = position;
		for (int i = 0; i < alignmentLength; i++) {
			if (alignment[i] != EDLIB_EDOP_INSERT)
				tIdx--;
		}
	}
	for (int start = 0; start < alignmentLength; start += 50) {
		// target
		printf("T: ");
		int startTIdx = -1;
		for (int j = start; j < start + 50 && j < alignmentLength; j++) {
			if (alignment[j] == EDLIB_EDOP_INSERT)
				printf("-");
			else
				printf("%c", target[++tIdx]);
			if (j == start)
				startTIdx = tIdx;
		}
		printf(" (%d - %d)\n", max(startTIdx, 0), tIdx);

		// match / mismatch
		printf("   ");
		for (int j = start; j < start + 50 && j < alignmentLength; j++) {
			printf(alignment[j] == EDLIB_EDOP_MATCH ? "|" : " ");
		}
		printf("\n");

		// query
		printf("Q: ");
		int startQIdx = qIdx;
		for (int j = start; j < start + 50 && j < alignmentLength; j++) {
			if (alignment[j] == EDLIB_EDOP_DELETE)
				printf("-");
			else
				printf("%c", query[++qIdx]);
			if (j == start)
				startQIdx = qIdx;
		}
		printf(" (%d - %d)\n\n", max(startQIdx, 0), qIdx);
	}
}

long long foo(int64_t* a, int64_t* b, size_t ii, size_t jj)
{

	for (size_t i = 0; i < ii; i++)
		for (size_t j = 0; j < jj; j++)
			auto g = b[i];

	auto s = tup(a, b);

	return 1;
}