#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib> 

// Utility Function (TODO: put into another file and import it)
int read_csv(const char* filename, float **x, float **y){
    // Variable Initialization
    int index = 0;
    int length = 0;

    // Reading File to get the number of x and y data points
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)){
        length++;
    }
    infile.close();

    // Mallocating space for x and y
    *x = (float *) std::malloc(sizeof(float)*length);
    *y = (float *) std::malloc(sizeof(float)*length);

    // Rereading the file to extract x and y values
    char comma;
    std::ifstream samefile(filename);
    while(std::getline(samefile,line)){
        std::stringstream line_stream(line);
        line_stream >> (*x)[index] >> comma >> (*y)[index];
        index++;
    }
    samefile.close();

    return length;
}


// Helper functions for Algorithm
float mean(float *y, int length){
    float total = 0;
    for(int i = 0; i < length; i++){
        total = total + y[i];
    }
    return (total/length);
}

float variance(float *y, int length){
    // Not the most efficient way of calculating variance, see : https://www.sciencebuddies.org/science-fair-projects/science-fair/variance-and-standard-deviation 
    float total = 0;
    float residual;
    float y_mean = mean(y,length);
    for(int i = 0 ; i < length; i++){
        residual = (y[i] - y_mean);
        total = total + (residual*residual);
    }
    return (total/length);
}

float residual_sum_of_square(float *y_pred, float *y_true, int length){
    float total = 0;
    
    return total;
}

int calculate_r2(float *y_pred, float *y_true, int length){
    // Taken from: https://en.wikipedia.org/wiki/Coefficient_of_determination
    // R^2 = 1 - (Sum of Squared Residual / Sum of Squared Total)
    // residuals (e) = y_true - y_pred
    // mean of observed data (y_mean) = mean(y_true)
    // Sum of squared total = sum from i = 0 to length-1 of (y_true_i - y_pred_i)^2
    // This is similar to variance(y) * length;
    return -1;
}

// This use Mean Square Error
int fit_linear_regression(int data){
    return -1;
}

int main(){
    float *x;
    float *y;
    int length; 
    const char* filename = "test.csv";
    length = read_csv(filename,&x,&y);

    std::cout << mean(x,length);
}

// TODO:
// Q: What types of data do we want to fit?
// A: Because this is linear regression we want to have a vector 'x' witht their corresponding 'y'
// This will be read from a CSV file
// Q: What type of output do we want for this function?
// A csv file with all the weight for the parameters


// NOTES:
// Following this tutorial:
// https://towardsdatascience.com/introduction-to-machine-learning-algorithms-linear-regression-14c4e325882a

// Linear Regression:
// y = a_0 + a_1 * x  
// we want to find the best a_0 and a_1 for the dataset

// Cost Function:
// Need a cost-function and want to minimize that (minimization problem now)
// Mean Squared Error = 1/n * (Sum (y_predi - yi)^2 from i = 1 to n)
// MSE is just a type of error we can choose from

// Gradient Descent
// Used to minimize MSE cost function to find best a_0 and a_1
// Big learning rate = big jumps, small learning rate = super small jumps (longer)
// If cost function not convex can be stuck in a local minima (not happening in linear regression)
// Need gradient, so we take partial derivative with respect to a_0 and a_1.
// Calculus is used to find partial derivative

// How to update
// a -> learning rate
// new_a0 = a0 - (2a/n)* (Sum (y_predi - yi) from i = 1 to n)
// new_a1 = a1 - (2a/n)* (Sum (y_predi - yi)*xi from i = 1 to n)

// How to calculate score (R2 score)
// Read more over here: https://en.wikipedia.org/wiki/Coefficient_of_determination
// Definition is:  proportion of the variance in the dependent variable that is predictable from the independent variable(s)