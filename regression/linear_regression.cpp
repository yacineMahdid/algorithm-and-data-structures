#include "utils.h"

// fit a line given some x and weights
void fit(float *x, float *weights, float *y_pred, int length){
    
    for(int i = 0; i < length; i++){
        y_pred[i] = weights[0] + weights[1]*x[i];
    }
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