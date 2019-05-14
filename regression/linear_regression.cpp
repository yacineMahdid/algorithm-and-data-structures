#include "utils.h"

// Model class for MSE Linear Regression
class LinearRegressionModel{
    // Models Variable
    float *x;
    float *y;
    int length;
    float *weights;

    // Public function for user
    public:
        // Constructor
        LinearRegressionModel(float *x_train, float *y_train, int length_train){
            // Setting Variables
            x = (float *) malloc(sizeof(float)*length_train);
            y = (float *) malloc(sizeof(float)*length_train);

            std::memcpy(x, x_train, sizeof(float)*length_train);
            std::memcpy(y, y_train, sizeof(float)*length_train);
            length = length_train;
            
            // Initializing Weights to 0
            weights = (float *) std::malloc(sizeof(float)*2);
            weights[0] = 0; // intercept
            weights[1] = 0; // slope
        }

        // Destructor
        ~LinearRegressionModel(){
            free(x);
            free(y);
            free(weights);
        }

        void print_weights(){
            std::cout << "y = " << weights[1] << "x + " << weights[0]  << "\n";
        }

        // Train the regression model with some data
        void train(int max_iteration, float learning_rate){

            // Mallocating some space for prediction
            float *y_pred = (float *) std::malloc(sizeof(float)*length);

            while(max_iteration > 0){
                fit(y_pred);
                update(y_pred, learning_rate);

                float mse = mean_squared_error(y_pred,y,length);

                if(max_iteration % 100 == 0){
                    std::cout << "Iteration left: " << max_iteration << "; MSE = " << mse << "\n";
                }
                max_iteration--;
            }
            free(y_pred);
        }

        float predict(float x_test){
            return weights[0] + weights[1]*x_test;
        }

    // Private function for algorithm
    private:
        // fit a line given some x and weights
        void fit(float *y_pred){
            
            for(int i = 0; i < length; i++){
                y_pred[i] = weights[0] + weights[1]*x[i];
            }
        }

        // Update using Gradient Descent
        void update(float *y_pred, float learning_rate){
                    
            float multiplier = 2*learning_rate/length;
            // update the intercept
            weights[0] = weights[0] - multiplier*(intercept_sum(y_pred,y,length));
            // update the slope
            weights[1] = weights[1] - multiplier*(slope_sum(x,y_pred,y,length));
        }
};


int main(){
    // Variable Initialization
    float *x_train;
    float *y_train;
    int length_train;
    const char* filename = "test.csv";
    length_train = read_csv(filename,&x_train,&y_train);

    // Regression Variables
    int max_iteration = 1000;
    float learning_rate = 0.1;

    // Training
    LinearRegressionModel linear_reg = LinearRegressionModel(x_train,y_train,length_train);
    linear_reg.train(max_iteration, learning_rate);
    
    // Testing
    float x_test = 123; // Should give us 124 for y
    float y_test = linear_reg.predict(x_test);
    linear_reg.print_weights();
    std::cout << "y = " << y_test << "\n"; 

}