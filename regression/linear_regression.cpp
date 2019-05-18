#include "utils.h"

// Model class for MSE Linear Regression
// Update: https://en.wikipedia.org/wiki/Linear_regression
class LinearRegressionModel{
    // Models Variable
    Dataset data;
    Weights weights;

    // Public function for user
    public:
        // Constructor
        LinearRegressionModel(float **X, float *y, int length_train, int number_predictor_train){
            // Setting Variables
            data = Dataset(X, y, length_train, number_predictor_train);
            weights = Weights(number_predictor_train, 1);
        }

        void print_weights(){
            char function_string[1000];
            strcpy(function_string, "y = ");
            for(int i = 0; i < weights.number_weights; i++){
                char weight[20];
                sprintf(weight,"%.2f * x%d",weights.values[i],i);
                strcat(function_string, weight);
                if(i == weights.number_weights-1){
                    strcat(function_string,"\n");
                }else{
                    strcat(function_string," + ");
                }
            }
            std::cout << function_string;
        }

        // Train the regression model with some data
        void train(int max_iteration, float learning_rate){

            // Mallocating some space for prediction
            float *y_pred = (float *) std::malloc(sizeof(float)*data.length);

            while(max_iteration > 0){
                fit(y_pred);
                weights.update(data, y_pred, learning_rate);

                float mse = mean_squared_error(y_pred,data.y,data.length);

                if(max_iteration % 100 == 0){
                    std::cout << "Iteration left: " << max_iteration << "; MSE = " << mse << "\n";
                }
                max_iteration--;
            }
            free(y_pred);
        }

        float predict(float *x){
            float prediction = 0;
                for(int i = 0; i < weights.number_weights; i++){
                    prediction = prediction + weights.values[i]*x[i];
                }
            return prediction;
        }

    // Private function for algorithm
    private:
        // fit a line given some x and weights
        void fit(float *y_pred){
            
            for(int i = 0; i < data.length; i++){
                y_pred[i] = predict(data.X[i]);
            }
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