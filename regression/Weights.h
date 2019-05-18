class Weights{
    private:
        int MAX_WEIGHTS;

    public:
        float* values;
        int number_weights;

        Weights();
        Weights(int number_predictor, int random_init);
        ~Weights();
        void update(Dataset data, float *y_pred, float learning_rate);
};