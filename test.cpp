#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>  
#include <stdlib.h>
#include <time.h> 
#include <typeinfo>

using namespace std;

class Function3D
{
    public:
        virtual vector <float> Point(float t) = 0;
        virtual vector <float> Derivative1(float t) = 0;

        friend ostream& operator <<(ostream& out, const Function3D& с);
        virtual ostream& output(ostream& out) { return out; }
        virtual float getinfo() { return 0.0f; }
        friend const bool operator>( Function3D& rh,  Function3D& lh);
        friend const bool operator+(Function3D& rh, Function3D& lh);
        
};

ostream& operator <<(ostream& out, Function3D& с) {
    return с.output(out);
}
const bool operator>( Function3D& rh,  Function3D& lh)
{
    return rh.getinfo()>lh.getinfo();
}
const bool operator+(Function3D& rh, Function3D& lh)
{
    return rh.getinfo() + lh.getinfo();
}

class circle: public Function3D
{
    private:
        float radius;
    public:
        explicit circle(float r) 
        {
            if (r >= 0)
            {
                radius = r;
            }
            else 
            { 
                r = 0;
                throw "the radius is not positive!"; 
            }
        }
                
        const bool operator>(const circle& rh) { return radius > rh.radius; }
        friend ostream& operator <<(ostream& out, const circle& с);
        friend const bool operator>(Function3D& rh, Function3D& lh);
        friend const bool operator+(Function3D& rh, Function3D& lh);
        virtual float getinfo() { return radius; }
        virtual vector <float> Point(float t) 
        {
            return { radius*cos(t),radius * sin(t),0}; 
        }
       
        virtual vector <float> Derivative1(float t)
        { 
            return  { - cos(t) / sin(t),0};
        }
        virtual ostream& output(ostream& out)
        {
            out << "circle with radius " << radius;
            return out;
        }
};

class ellips : public Function3D
{
private:
    float a;
    float b;
public:
    explicit ellips(float ai, float bi)
    {
        if (ai <= 0 || bi<=0)
        {
            throw "the radius is not positive!";
            a = b = 0;
        }
        else
        {
            if (ai > bi)
            {
                a = ai;
                b = bi;
            }
            else
            {
                a = bi;
                b = ai;
            }
        }
    }

    virtual vector <float> Point(float t)
    {
        return { a * cos(t),b * sin(t),0 };
    }

    virtual vector <float> Derivative1(float t)
    {
        return { -(b * cos(t)) / (a * sin(t)),0 };
    }
};

class Helix : public Function3D
{
private:
    float radius;
    float step;
public:
    explicit Helix(float a, float b)
    {
        if (a <= 0 || b <= 0)
        {
            throw "the radius is not positive!";
            step = radius = 0;
        }
        else
        {
            radius = a;
            step = b;
        }
    }

    virtual vector <float> Point(float t)
    {
        return { radius * cos(t),radius * sin(t),step * t};
    }

    virtual vector <float> Derivative1(float t)
    {
        return  { -step / sqrt(1 - cos(t) * cos(t)) , step / sqrt(1 - sin(t) * sin(t)) };
    }
};

float GetRandomNumberFloat(float min, float max, int precision)
{
    
    float value;
    value = rand() % (int)pow(10, precision);
    value = min + (value / pow(10, precision)) * (max - min);
    return value;
}
void print(std::vector<float> & input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

template<typename T>
void printVector(const vector<T>& vec) {
    for (auto i : vec) {
        cout << *i << "; ";
        
    }
    cout << endl;
}
template<typename T>
void bubbleSort(vector<T> &vec) {
    for (int i = 0; i < vec.size() - 1; ++i) {
        for (int j = 0; j < vec.size() - i - 1; ++j) {
            if ( *vec.at(j) >  *vec.at(j + 1))
                swap(vec.at(j), vec.at(j + 1));
        }
    }
}

int main()
{
    try
    {
        vector <Function3D*> functions;
        size_t n = 15;
        int choice;
        float number1, number2;
        srand(time(NULL));
        Function3D* newelement;

        for (int i=0; i < n; i++)
        {
            number1 = GetRandomNumberFloat(0.1f, 10.0f, 2);
            number2 = GetRandomNumberFloat(0.1f, 10.0f, 2);
            choice = rand() % 3;
            
            if (choice == 0) {
                functions.push_back(new circle(number1));
            }
            else if (choice == 1) {
                functions.push_back(new ellips(number1, number2));
            }
            else{
                newelement = new Helix(number1, number2);
                functions.push_back(newelement);
            }
        }
        cout << endl << "3.1 Coordinates of points  of all curves in the container at t=PI/4" << endl;
        for (int i = 0; i < n; i++)
        {
            vector <float> a = functions.at(i)->Point(M_PI / 4);
            cout << endl;
            print(a);
        }
        cout << endl << "3.2 Coordinates of derivatives  of all curves in the container at t=PI/4" << endl;
        for (int i = 0; i < n; i++)
        {
            vector <float> a = functions.at(i)->Derivative1(M_PI / 4);
            cout << endl;
            print(a);
        }

        vector <Function3D*> functions2;
        
        for (int i = 0; i < n; i++)
        {
            newelement = functions.at(i);
            if (typeid(*newelement) == typeid(circle))
            {
                functions2.emplace_back(newelement);
            }
        }
        cout << endl << "5. Sort the second container in the ascending order of circles’ radii" << endl;

        printVector(functions2);
        bubbleSort(functions2);
        printVector(functions2);

        float ss = 0;
        for (int i = 0; i < functions2.size(); i++)
        {
            ss += functions2.at(i)->getinfo();
        }
        cout << endl << "6. Total sum of radii of all curves in the second container" << ss << endl;


        for (int i = 0; i < n; i++)
        {
            delete[] functions.at(i);
            
        }
        

        
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
}

