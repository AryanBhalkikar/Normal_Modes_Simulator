#include <iostream>
#include <fstream>
#include "gnuplot-iostream.h"

#define PI 3.14159

void plotter(int N, int counter, double delay){
    Gnuplot gp;
    gp << "set term gif animate " << delay << " font 'Helvetica,16' enhanced\n";
    gp << "set output 'oscillations.gif'\n";
    gp << "set xrange [0:" << N+1 <<"]\n";
    gp << "set yrange [-1.5:1.5]\n";
    gp << "unset key\n";
    gp << "set grid\n";
    gp << "set xlabel 'Particle Number'\n";
    gp << "set ylabel 'Amplitude'\n";
    gp << "set xtics 0, 1," << N+1 << "\n";
    gp << "do for [i = 0:" << counter <<"] {plot '/Users/anirudh/Documents/Physics Project Gnu/data.txt' index i w lines}\n";
}

void amplitudeFunction(double w, std::vector<std::pair<int,double> > A0, int N){

    std::ofstream op ("data.txt");

    double timePeriod = 2*PI/w;
    int counter = 0;
    double delay = 0.1;
    std::vector<std::pair<int, double> > A;
    
    for (double t = 0; t < 5*timePeriod; t = t+delay){

        A = A0;

        double coswtValue = std::cos(w*t);

        for (auto &i: A){
            i.second = (i.second) * coswtValue;
        }
        
        for (auto i: A){
            op << i.first << " " << i.second << std::endl;
        }
        op << std::endl << std::endl;
        counter++;
    }

    op.close();

    plotter(N, counter, delay);
}

void findMaxAmp(int n, int N, double w){
    int C = 1;
    int p = 0;

    std::vector<std::pair<int, double> > A0;

    double ampSinConstant = PI * n / (N+1);
    for (p = 0; p <= N; p++){
        double maxAmpOfP = C * std::sin(ampSinConstant*p);
        A0.push_back(std::make_pair(p, maxAmpOfP));
    }
    A0.push_back(std::make_pair(N+1, 0));
    amplitudeFunction(w, A0, N);
}

double naturalAngFreq(double T, double m, double l){
    return pow(T/(m*l), 0.5);
}

double angFreq(double naturalAngFreq, int N, int n){
    double freqSinConstant = PI * n / (2*(N+1));
    return (2*naturalAngFreq*std::sin(freqSinConstant));
}

int main(){
    int N, n;
    std::cout << "Enter the number of masses: ";
    std::cin >> N;

    while (N < 1){
        std::cout << "INVALID INPUT\nTry again: ";
        std::cin >> N;
    }

    std::cout << "Enter n for the nth normal mode: ";
    std::cin >> n;

    while (n < 0 || n > N){
        std::cout << "INVALID INPUT\nTry again: ";
        std::cin >> n;
    }

    double T, m, l;

    std::cout << "Enter value of Tension (in Newton): ";
    std::cin >> T;

    while (T < 0){
        std::cout << "INVALID INPUT\nTry again: ";
        std::cin >> T;
    }

    std::cout << "Enter mass of each particle (in Kg): ";
    std::cin >> m;

    while (m < 0){
        std::cout << "INVALID INPUT\nTry again: ";
        std::cin >> m;
    }

    std::cout << "Enter length of string (in meters): ";
    std::cin >> l;

    while (l < 0){
        std::cout << "INVALID INPUT\nTry again: ";
        std::cin >> l;
    }

    double w0 = naturalAngFreq(T, m, l);
    double w = angFreq(w0, N, n);
    findMaxAmp(n, N, w);
}