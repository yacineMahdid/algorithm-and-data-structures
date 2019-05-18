#include "utils.h"

class Dataset{
    public:
        float **X;
        float *y;
        int number_predictor; //including intercept
        int length;

        Dataset(float **X_train,float *y_train, int length_train, int number_predictor_train){
            X = (float **) malloc(sizeof(float*)*number_predictor);
            for(int i = 0; i < number_predictor_train+1; i++){
                X[i] = (float *) malloc(sizeof(float*)*length_train);
                std::memcpy(X[i], X_train[i], sizeof(float)*length_train);
            }

            // Setting the first element to 1 (as it is the Intercept)
            for(int i = 0; i < length_train; i++ ){
                X[0][i] = 1;
            }

            y = (float *) malloc(sizeof(float)*length_train);
            std::memcpy(y, y_train, sizeof(float)*length_train);
            
            length = length_train;
            number_predictor = number_predictor_train+1;
        }

        ~Dataset(){
            free(X);//Might need to free each malloc I did
            free(y);
        }
};

class Weights{
    private:
        int MAX_WEIGHTS;

    public:
        float* values;
        int number_weights;
        Weights(int number_predictor, int random_init){
            // Random Init Variables
            MAX_WEIGHTS = 100;
            srand(time(0));  // random number generator

            number_weights = number_predictor + 1; // +1 for the intercept
            values = (float *) std::malloc(sizeof(float)*number_weights);
            for(int i=0; i<number_weights; i++){
                if(random_init){
                    values[i] = (rand() % MAX_WEIGHTS);
                }else{
                    values[i] = 0;
                }
            }
        }

        ~Weights(){
            free(values);
        }

        void update(Dataset data, float *y_pred, float learning_rate){
            float multiplier = learning_rate/data.length;
            // Update each weights
            for(int i = 0; i < number_weights; i++){
                values[i] = values[i] - multiplier*(sum_residual(data.X[i],data.y,y_pred,data.length));
            }
        }
};


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

int make_csv(const char* filename, float* weights, int number_weights, int number_simulation){

}

// Stats Helper function
float mean(float *y, int length){
    float total = 0;
    for(int i = 0; i < length; i++){
        total = total + y[i];
    }
    return (total/length);
}

float sum_residual(float *x, float *y_true, float *y_pred, int length){
    float total = 0;
    float residual;
    for(int i = 0 ; i < length; i++){
        residual = (y_pred[i] - y_true[i]);
        total = total + residual*x[i];
    }
    return total;
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
