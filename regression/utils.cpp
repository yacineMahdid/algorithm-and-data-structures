#include "utils.h"

// Misc Helper function 
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

// Stats Helper function
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
