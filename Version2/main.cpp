/*

Problems: 
    1. Repeating values in data.txt
    2. last mode not giving 0 amplitude

*/




#include <iostream>
#include <fstream>

#define PI 3.14159

void amplitudeFunction(double w, std::vector<std::pair<int,double> > A){

    double timeConstant = PI / (2 * w);
    std::ofstream op ("data.txt");
    
    for (int t = 0; t < 10; t++){

        double coswtValue = std::cos(w*t*timeConstant);

        for (auto i: A){
            i.second = (i.second) * coswtValue;
        }
        
        for (auto i: A){
            op << i.first << " " << i.second << std::endl;
        }
        op << std::endl << std::endl;
    }

    op.close();
}

void findMaxAmp(int n, int N, double w){
    int C = 1;
    int p = 0;

    std::vector<std::pair<int, double> > A0;

    double ampSinConstant = PI * n / (N+1);
    for (p = 0; p <= N+1; p++){
        double maxAmpOfP = C * std::sin(ampSinConstant*p);
        A0.push_back(std::make_pair(p, maxAmpOfP));
    }
    amplitudeFunction(w, A0);
}

double naturalAngFreq(double T, double m, double l){
    return pow(T/(m*l), 0.5);
}

double angFreq(double naturalAngFreq, int N, int n){
    int freqSinConstant = PI * n / (2*(N+1));
    return 2*naturalAngFreq*std::sin(freqSinConstant);
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