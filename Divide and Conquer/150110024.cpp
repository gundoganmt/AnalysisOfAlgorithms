#include <iostream>
#include <float.h>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

struct Point{
    int x, y, z;
};

class DivideConquer{
	private:
		Point *P;
		int count;
		double total_time;
	public:
		DivideConquer(int N){
			P = new Point[N];
			count = 0;
		}
		void ReadFile(char *filename);
		float closest(int);
		~DivideConquer(){
			delete P;
		}
		int getCount(){ return count; }
		float getTime(){ return total_time; }
		float bruteForce(Point [], int);
		float closestPair(Point [], Point [], int );
		float stripDistance(Point [], int, float);
};

int compareX(const void* a, const void* b){
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b){
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y - p2->y);
}

int compareZ(const void* a, const void* b){
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->z - p2->z);
}

// A utility function to find the distance between two points
float dist(Point p1, Point p2){
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y) +
                 (p1.z - p2.z)*(p1.z - p2.z)
               );
}

float DivideConquer::bruteForce(Point P[], int n){
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min){
            	min = dist(P[i], P[j]);
            	count++;
			}
    return min;
}

// A utility function to find minimum of two float values
float min(float x, float y){
    return (x < y) ? x : y;
}

float DivideConquer::stripDistance(Point strip[], int size, float d){
    float min = d;

    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i],strip[j]) < min){
            	min = dist(strip[i], strip[j]);
            	count++;
			}
    return min;
}

float DivideConquer::closestPair(Point Px[], Point Py[], int n){
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(Px, n);

    int mid = n/2;
    Point midPoint = Px[mid];

    Point Pyl[mid+1];
    Point Pyr[n-mid-1];
    int li = 0, ri = 0;
    for (int i = 0; i < n; i++){
      	if (Py[i].x <= midPoint.x)
         	Pyl[li++] = Py[i];
      	else
         	Pyr[ri++] = Py[i];
        count++;
    }

    float dl = closestPair(Px, Pyl, mid);
    float dr = closestPair(Px + mid, Pyr, n-mid);

    float d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    return min(d, stripDistance(strip, j, d) );
}

float DivideConquer::closest(int n){
    Point Px[n];
    Point Py[n];
    Point Pz[n];

    for (int i = 0; i < n; i++){
        Px[i] = P[i];
        Py[i] = P[i];
        Pz[i] = P[i];
    }

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);
	qsort(Pz, n, sizeof(Point), compareZ);

    return closestPair(Px, Py, n);
}

void DivideConquer::ReadFile(char *filename){
	ifstream infile(filename);
	int i = 0;
	int n;
	infile >> n;
	Point pt;
	while(i < n){
		infile >> pt.x >> pt.y >> pt.z;
		P[i] = pt;
		i++;
	}
	infile.close();
}

int ReadFileSize(char *filename){
	ifstream infile(filename);
	int n;
	infile >> n;
  	infile.close();
	return n;
}

int main(int argc, char *argv[]){

	int N = ReadFileSize(argv[1]);
	DivideConquer dc(N);

    dc.ReadFile(argv[1]);
    clock_t begin = clock();
    cout << "The smallest distance is " << dc.closest(N) << endl;
    clock_t end = clock();
    cout << "total number of distance calculation " << dc.getCount() << endl;
    cout.precision(5);
    cout << "total running time " << fixed << (double)(end-begin)*1000/CLOCKS_PER_SEC << " miliseconds" << endl;
    return 0;
}

