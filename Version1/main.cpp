#include <iostream>
#include <vector>
#include "gnuplot-iostream.h"

#define PI 3.1415926

void plotPoints(std::vector<std::pair<int,double>> point, int N){

    Gnuplot gp;

    gp << "set title 'Amplitude of Normal Modes'\n";
    gp << "set xlabel 'Particle Number'\n";
    gp << "set ylabel 'Amplitude'\n";
    gp << "set grid\n";
    gp << "set xrange [0:" << N+1 << "]\n";
    gp << "set yrange [-1.5:1.5]\n";
    gp << "set xtics 0, 1," << N+1 << "\n";
    gp << "set terminal qt size 800,600 position 100,100\n";
    gp << "plot '-' with lines title 'y'\n";

    gp.send1d(point);

}


void getPoints(int N, int n){

    double constArg = ((PI * n)/(N+1));
    std::vector<std::pair<int,double>> point;

    double arg, A;
    int C = 1;

    for (int p = 0; p <= N+1; p++){
        arg = p * constArg;
        A = C * std::sin(arg);

        point.push_back(std::make_pair(p, A));
    }

    plotPoints(point, N);
}


int main(){

    int n, N;

    std::cout << "Enter the number of masses: ";
    std::cin >> N;

    while (N < 0){
        std::cout << "Invalid input. Try again: " << std::endl;
        std::cin >> N;
    }

    std::cout << "Enter mode: ";
    std::cin >> n;

    while (n < 0 || n > N){
        std::cout << "Invalid input. Try again: " << std::endl;
        std::cin >> n;
    }

    getPoints(N, n);

    return 0;
}