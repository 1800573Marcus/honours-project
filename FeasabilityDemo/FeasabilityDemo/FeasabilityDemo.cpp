// FeasabilityDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <fstream> 
#include <time.h>
#include <iostream>
#include <string>
using namespace std;

struct coordinate {//struct used for fitness function
	int x;
	int y;
	bool checked = false;
};

int fitness(int map[20][20]) { //fitness algorithm takes in a map
	//std::cout << "fitness test " << std::endl;

	int directions[4][2]{ -1, 0,
							  1, 0,
							  0, -1,
							  0, 1 }; //directions for moving 
	int distance = 1;
	int distancelooped = 0;
	bool foundtarget = false;
	bool nextsteppossible = true;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {

			if (map[i][j] == -2) {
				map[i][j] = distance; // find and mark start point
			}
		}
	}
	while (foundtarget == false) { //until target found
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {//check every coordinate

				if (map[i][j] == distance) { //find where the path has reached
					for (int h = 0; h < 4; h++) {  //check coords around newest point
						if (map[i + directions[h][0]][j + directions[h][1]] == -3) { //if target found stop
							foundtarget = true;

						}
						else if (map[i + directions[h][0]][j + directions[h][1]] == -1) {//if the coord is in a tuneel mark it for the next loop
							map[i + directions[h][0]][j + directions[h][1]] = distance + 1;

						}


					}
				}

			}



		}

		
		distance++;//increase distance to check next section of the path
		nextsteppossible = false;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (map[i][j] == distance) {
					nextsteppossible = true;
				}

			}
		}
		if (nextsteppossible == false) {
			return 0;
		}
	}
	//std::cout << "fitness result " << distance << std::endl;

	return distance;


}

void geneicAlgorithm(int map[20][20][20]) {
	std::cout << "genetic  algorithm" << std::endl;
	string filename;
	for (int h = 0; h < 20; h++) {

		filename = "test map" + std::to_string(h) + ".ppm";//set up for exporting maps to image
		ofstream img(filename);
		img << "P3" << endl;
		img << 20 << " " << 20 << endl;
		img << "255" << endl;

		for (int i = 0; i < 20; i++) {

			for (int j = 0; j < 20; j++) {
				//std::cout << map[i][j];
				if (map[h][i][j] == -1) { //output an image marking the start, end and tunnels with appropriate colours

					img << 0 << " " << 250 << " " << 5 << endl;

				}
				else  if (map[h][i][j] == 0) {
					img << 200 << " " << 5 << " " << 50 << endl;


				}
				else  if (map[h][i][j] == -2) {
					img << 100 << " " << 5 << " " << 200 << endl;


				}
				else  if (map[h][i][j] == -3) {
					img << 120 << " " << 5 << " " << 125 << endl;


				}
			}

		}
	}

	int fitnessscores[20]; // array for fitness score
	bool converged = false; //bool for tracking convergence
	int parents[2]; //parent values
	int parentval;
	int weakest;
	int weakestpos; //weakest values
	int mutatonresult;
	int parentval2;
	int offspring[20][20]; //array for tracking offspring maps
	int x;
	int y;
	bool mutation = false; //bool to control mutation
	int mutationchance = 0;
	int randnum = 0;

	while (converged == false) { //until population congerges keep evolving
		//std::cout << "still looping genetic" << std::endl;

		for (int i = 0; i < 20; i++) {
			fitnessscores[i] = fitness(map[i]);//get fitness sores of starting maps
		}
		parentval = fitnessscores[0];
		parentval2 = fitnessscores[0];
		weakest = fitnessscores[0];
		weakestpos = 0;
		parents[0] = 0;
		parents[1] = 0;
		if (map[0] == map[1] && map[0] == map[2] && map[0] == map[3] && map[0] == map[4] && map[0] == map[5] && map[0] == map[6] && map[0] == map[7] && map[0] == map[8] && map[0] == map[9] && map[0] == map[10] && map[0] == map[11] && map[0] == map[12] && map[0] == map[13] && map[0] == map[14] && map[0] == map[15] && map[0] == map[16] && map[0] == map[17] && map[0] == map[18] && map[0] == map[19]) { //check convergence
			converged = true;
		}
		for (int i = 0; i < 20; i++) {
			if (fitnessscores[i] > parentval) {
				parentval = fitnessscores[i]; //find best fitness value
				parents[0] = i;

			}
		}
		//cout << "best val " << fitnessscores[parents[0]] << endl;
		for (int i = 0; i < 20; i++) {
			if (fitnessscores[i] >= parentval2 && i != parents[0]) {
				parentval2 = fitnessscores[i];
				parents[1] = i; // find second best fitness value
			}
		}
		//cout << "breeding " << parents[0] << " with " << parents[1] << endl;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				offspring[i][j] = map[parents[0]][i][j]; //put best parent value into offspring array
			}
		}
		//for (int i = 0; i < 5; i++) {
			x = rand() % 19;
			y = rand() %19;
			offspring[x][y] = map[parents[1]][x][y]; //select random pointd from second parent and combine with the first parent


		//}
		for (int i = 0; i < 20; i++) {
			if (fitnessscores[i] < weakest) {
				weakest = fitnessscores[i]; //find the weakest fitness score
				weakestpos = i;
			}
		}
	//cout << "weakest value was " << weakestpos << "With a value of " << weakest << endl;

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				map[weakestpos][i][j] = offspring[i][j];//replace weakest map with offspring of both parents 
			}
		}


		randnum = x = rand() % 5 + 1;  //if the random number is smaller than the mutation chance then mutate the data
		if (randnum <= mutationchance) {
			//std::cout << "mutation " << std::endl;
			mutationchance = 0; //reset mutation chance
			for (int i = 0; i < 5; i++) {

				randnum = x = rand() % 19;
				mutatonresult = rand() % 4;
				if (mutatonresult == 0) {
					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = -1; //randomly change data
				}
				if (mutatonresult == 1) {

					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = -2; //randomly change data

				}
				if (mutatonresult == 2) {

					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = -3; //randomly change data
				}
				if (mutatonresult == 3) {
					map[randnum][rand() % 19 + 1][rand() % 19 + 1] = 0; //randomly change data

				}

			}



			

		}
		mutationchance++; //increase mutation chance over time
		
		

	}
	 filename = "Genetic map.pmm";

	ofstream img(filename);
	img << "P3" << endl;
	img << 20 << " " << 20 << endl;
	img << "255" << endl;


	// writing pixel data
	
		for (int i = 0; i < 20; i++) {

			for (int j = 0; j < 20; j++) {
				//std::cout << map[i][j];
				if (map[0][i][j] == -1) { //output an image marking the start, end and tunnels with appropriate colours

					img << 0 << " " << 250 << " " << 5 << endl;

				}
				else  if (map[0][i][j] == 0) {
					img << 200 << " " << 5 << " " << 50 << endl;


				}
				else  if (map[0][i][j] == -2) {
					img << 100 << " " << 5 << " " << 200 << endl;


				}
				else  if (map[0][i][j] == -3) {
					img << 120 << " " << 5 << " " << 125 << endl;


				}
			}
		
	}
	
	
	std::cout << "genetic  algorithm finished" << std::endl;

}





int main()
{
	srand(time(NULL));//set up for random numbers
	int map[20][20][20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,//initialised map grid
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	int maxtunnels = 50;//variables for controlling map generation
	int maxlength = 15;
	int tunnellength;
	int randlength;
	int directions[4][2]{ -1, 0,// 2d array used to move through grid
							  1, 0,
							  0, -1,
							  0, 1 };
	int currentx;
	int currenty;//variables for current position in map
	int lastDirection[2]{ 0,0 };// tracks last direction traveled
	int randomDirection[2];// used to select new direction 
	int firstdirection;
	string filename;
	for (int h = 0; h < 20; h++) { //loop to generate 20 maps  
		maxtunnels = 50;//reset max tunnels 
		filename = "map" + std::to_string(h) + ".ppm";//set up for exporting maps to image

		 currentx = rand() % 20 + 1.;//choose random start position
		 currenty = rand() % 20 + 1.;
		map[h][currentx][currenty] = -2;// mark start position
		 firstdirection = rand() % 3 + 0; //choose a random diresction
		randomDirection[0] = directions[firstdirection][0];
		randomDirection[1] = directions[firstdirection][1];
		while (maxtunnels > 0) { // wander until max amount of tunnels has been generated 

			while ((randomDirection[0] == -lastDirection[0] && randomDirection[1] == -lastDirection[1]) || (randomDirection[0] == lastDirection[0] && randomDirection[1] == lastDirection[1])) { //loop until i new direction that isnt backwards is chosen
				if (currentx == 1 && currenty == 1 && lastDirection[0] == 0 && lastDirection[1] == -1) { //if in top left corner and going up go right

					randomDirection[0] = directions[1][0];
					randomDirection[1] = directions[1][1];
					break;
				}
				else if (currentx == 1 && currenty == 1 && lastDirection[0] == -1 && lastDirection[1] == 0) { //if in top left and going left go down

					randomDirection[0] = directions[3][0];
					randomDirection[1] = directions[3][1];
					break;
				}
				if (currentx == 1 && currenty == 18 && lastDirection[0] == 0 && lastDirection[1] == 1) { //if in bottom left and going down go right

					randomDirection[0] = directions[1][0];
					randomDirection[1] = directions[1][1];
					break;
				}
				else if (currentx == 1 && currenty == 18 && lastDirection[0] == -1 && lastDirection[1] == 0) {//if in bottom left and going left go up

					randomDirection[0] = directions[2][0];
					randomDirection[1] = directions[2][1];
					break;
				}if (currentx == 18 && currenty == 1 && lastDirection[0] == 1 && lastDirection[1] == 0) { //if in top right  and going right go down

					randomDirection[0] = directions[3][0];
					randomDirection[1] = directions[3][1];
					break;
				}
				else if (currentx == 18 && currenty == 1 && lastDirection[0] == 0 && lastDirection[1] == -1) { // if in top right and going up go left

					randomDirection[0] = directions[0][0];
					randomDirection[1] = directions[0][1];
					break;
				}if (currentx == 18 && currenty == 18 && lastDirection[0] == 1 && lastDirection[1] == 0) {//if in bottom right  and going down turn left

					randomDirection[0] = directions[2][0];
					randomDirection[1] = directions[2][1];
					break;
				}
				else if (currentx == 18 && currenty == 18 && lastDirection[0] == 0 && lastDirection[1] == 1) { // if in bottom right and going rght turn up

					randomDirection[0] = directions[1][0];
					randomDirection[1] = directions[1][1];
					break;
				}
				if (currentx == 1 && (lastDirection[0] == 0 && lastDirection[1] == -1 || lastDirection[0] == 0 && lastDirection[1] == 1)) { //if at left side and going up or down then turn right

					randomDirection[0] = directions[1][0];
					randomDirection[1] = directions[1][1];
					break;
				}
				if (currenty == 1 && (lastDirection[0] == -1 && lastDirection[1] == 0 || lastDirection[0] == 1 && lastDirection[1] == 0)) { //if at top side and going left or right then turn down

					randomDirection[0] = directions[3][0];
					randomDirection[1] = directions[3][1];
					break;
				}
				if (currentx == 18 && (lastDirection[0] == 0 && lastDirection[1] == -1 || lastDirection[0] == 0 && lastDirection[1] == 1)) { //if at right side and going up or down then turn left

					randomDirection[0] = directions[2][0];
					randomDirection[1] = directions[2][1];
					break;
				}
				if (currenty == 18 && (lastDirection[0] == -1 && lastDirection[1] == 0 || lastDirection[0] == 1 && lastDirection[1] == 0)) { //if at bottom side and going left or right then turn up

					randomDirection[0] = directions[1][0];
					randomDirection[1] = directions[1][1];
					break;
				}

				firstdirection = rand() % 3 + 0; //pick random direction
				randomDirection[0] = directions[firstdirection][0];
				randomDirection[1] = directions[firstdirection][1];


			}

			randlength = rand() % maxlength + 1; //pick a random length for current tunnel
			tunnellength = 0;

			while (tunnellength <= randlength) { //check ourr current tunnel has a lenght
				if (((currentx == 1) && (randomDirection[0] == -1)) ||
					((currenty == 1) && (randomDirection[1] == -1)) ||
					((currentx == 18) && (randomDirection[0] == 1)) ||
					((currenty == 18)) && (randomDirection[1] == 1))

				{
					lastDirection[0] = randomDirection[0];
					lastDirection[1] = randomDirection[1];
					break; //if  weve hit an edge break to chose a new direction
				}
				else {
					if (map[h][currentx][currenty] != -2) {
						map[h][currentx][currenty] = -1; //mark new map location
					}
					currentx += randomDirection[0];
					currenty += randomDirection[1];// move to next position
					tunnellength++;


				}


			}

			if (tunnellength > 0) {
				lastDirection[0] = randomDirection[0];
				lastDirection[1] = randomDirection[1];


				maxtunnels--; //countdown max tunnels

			}

		}
		map[h][currentx][currenty] = -3;// mark end position


		
	}
	std::cout << "generation finished" << std::endl;

	ofstream img(filename);
	img << "P3" << endl;
	img << 20 << " " << 20 << endl;
	img << "255" << endl;


	// writing pixel data
	for (int h = 0; h < 20; h++) {
		for (int i = 0; i < 20; i++) {

			for (int j = 0; j < 20; j++) {
				//std::cout << map[i][j];
				if (map[h][i][j] == -1) { //output an image marking the start, end and tunnels with appropriate colours

					img << 0 << " " << 250 << " " << 5 << endl;

				}
				else  if (map[h][i][j] == 0) {
					img << 200 << " " << 5 << " " << 50 << endl;


				}
				else  if (map[h][i][j] == -2) {
					img << 100 << " " << 5 << " " << 200 << endl;


				}
				else  if (map[h][i][j] == -3) {
					img << 120 << " " << 5 << " " << 125 << endl;


				}
			}
		}
	}

	geneicAlgorithm(map);
}


