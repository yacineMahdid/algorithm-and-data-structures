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

float sum_of_square(float *y, int length){
    // Not the most efficient way of calculating variance, see : https://www.sciencebuddies.org/science-fair-projects/science-fair/variance-and-standard-deviation 
    float total = 0;
    float residual;
    float y_mean = mean(y,length);
    for(int i = 0 ; i < length; i++){
        residual = (y[i] - y_mean);
        total = total + (residual*residual);
    }
    return total;
}

float residual_sum_of_square(float *y_pred, float *y_true, int length){
    float total = 0;
    float residual;
    for(int i = 0 ; i < length; i++){
        residual = (y_true[i] - y_pred[i]);
        total = total + (residual*residual);
    }
    return total;
}

int calculate_r2(float *y_pred, float *y_true, int length){
    // Taken from: https://en.wikipedia.org/wiki/Coefficient_of_determination
    float sum_squared_residual = residual_sum_of_square(y_pred,y_true,length);
    float sum_squared_total = sum_of_square(y_true,length);
    return (1 - ((sum_squared_residual/sum_squared_total)));
}

float mean_squared_error(float *y_pred, float *y_true, int length){
    return residual_sum_of_square(y_pred,y_true,length)/length;
}

// fit a line given some x and weights
void fit(float *x, float *weights, float *y_pred, int length){
    
    for(int i = 0; i < length; i++){
        y_pred[i] = weights[0] + weights[1]*x[i];
    }
}

float intercept_sum(float *y_pred, float *y_true, int length){
    float total = 0;
    float residual;
    for(int i = 0 ; i < length; i++){
        residual = (y_pred[i] - y_true[i]);
        total = total + residual;
    }
    return total;
}

float slope_sum(float *x, float *y_pred, float *y_true, int length){
    float total = 0;
    float residual;
    for(int i = 0 ; i < length; i++){
        residual = (y_pred[i] - y_true[i]);
        total = total + residual*x[i];
    }
    return total;
}

void update(float *x, float *y_true, float *y_pred, float *weights, float learning_rate, int length){
    // How to update
    // a -> learning rate
    // new_a0 = a0 - (2a/n)* (Sum (y_predi - yi) from i = 1 to n)
    // new_a1 = a1 - (2a/n)* (Sum (y_predi - yi)*xi from i = 1 to n)
    
    float multiplier = 2*learning_rate/length;
    // update the intercept
    weights[0] = weights[0] - multiplier*(intercept_sum(y_pred,y_true,length));
    // update the slope
    weights[1] = weights[1] - multiplier*(slope_sum(x,y_pred,y_true,length));
}

// This use Mean Square Error
float* linear_regression(float *x, float *y, int length){
    // This function will return an array of 2 items (intercept and slope)
    float *weights = (float *) std::malloc(sizeof(float)*2);
    float *y_pred = (float *) std::malloc(sizeof(float)*length);
    // Here we will use gradient descent to find the best fit
    int max_epoch_left = 10000;
    float learning_rate = 0.001;
    weights[0] = 0; // intercept
    weights[1] = 0; // slope
    while(max_epoch_left > 0){
        fit(x,weights,y_pred,length);
        update(x, y, y_pred, weights, learning_rate, length);
        float mse = mean_squared_error(y_pred,y,length);
        std::cout << mse << "\n";
        max_epoch_left--;
    }
    free(y_pred);
    return weights;
}

int main(){
    float *x;
    float *y;
    int length; 
    const char* filename = "test.csv";
    length = read_csv(filename,&x,&y);
    float *weights = linear_regression(x,y,length);
    std::cout << "y = " << weights[1] << "x + " << weights[0]  << "\n";
}

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