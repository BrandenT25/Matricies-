#include <iostream>
#include <cassert>

template <size_t N>
class Matrix{
    private:
        size_t rows;
        size_t cols;
        int* matrix_content; 
        int matrix_size = rows * cols;
    public:
    Matrix(size_t rows, size_t cols){
        this->rows = rows;
        this->cols = cols;
        this->matrix_size = rows * cols;
        this->matrix_content = new int[matrix_size];
    }
    Matrix(int(&arr)[N], size_t row, size_t col){
        this->rows = row;
        this->cols = col;
        matrix_size = rows * cols;
        matrix_content = new int[matrix_size];
        assert(N <= matrix_size);
        for(size_t i{0}; i < N; ++i){
            matrix_content[i] = arr[i];
        }
        for(size_t i{N}; i < matrix_size; ++i){
            matrix_content[i] = 0;
        }
    }
    Matrix (const Matrix& other){
        this->matrix_size = other.matrix_size;
        this->rows = other.rows;
        this->cols = other.cols;
        this->matrix_content = new int[matrix_size];
        for(size_t i{0}; i < matrix_size; ++i){
            this->matrix_content[i] = other.matrix_content[i];
        }
    }

    Matrix& operator=(const Matrix& other){
        if(this == &other){
            return *this;
        }
        this->matrix_size = other.matrix_size;
        int* old_content = this->matrix_content;
        this->matrix_content = new int[matrix_size];
        this->rows = other.rows;
        this->cols = other.cols;
        delete[] old_content;
        for(size_t i{0}; i < matrix_size; ++i){
            this->matrix_content[i] = other.matrix_content[i];
        }
        return *this;
    }
    Matrix(Matrix&& other) noexcept{
    
        this->matrix_size = other.matrix_size;
        this->cols = other.cols;
        this->rows = other.rows;
        this->matrix_content = std::move(other.matrix_content);
        other.rows = 0;
        other.cols = 0;
        other.matrix_size = 0;
        other.matrix_content = nullptr;
        
    }
    Matrix& operator=(Matrix&& other) noexcept{
        if(this == &other){
            return *this;
        }
        this->rows = other.rows;
        delete[] matrix_content;
        this->matrix_size = other.matrix_size;
        this->cols = other.cols;
        matrix_content = std::move(other.matrix_content);
        other.rows = 0;
        other.cols = 0;
        other.matrix_size = 0;
        other.matrix_content = nullptr;
        return *this;
    }
    ~Matrix(){
        delete[] matrix_content;
    }
    Matrix operator+(const Matrix& other) const{
        assert(other.rows == this->rows);
        assert(other.cols == this->cols);
        Matrix result(rows, cols);
        for(size_t i{0}; i <= rows-1; i++){
            for(size_t j{0};  j <= cols-1; j++){
                size_t index = i * cols + j;
                result.matrix_content[index] = this->matrix_content[index] + other.matrix_content[index];
            }
        }
        return(result);
    }

    void print_matrix(){
        for(size_t i{0}; i <= rows - 1; ++i){
            std::cout << "[";
            for(size_t j{0}; j <= cols - 1; ++j){
                size_t element_index = i * cols + j;
                if(!(j == 0)){
                    std::cout << ", ";
                }
                std::cout << matrix_content[element_index];
            }
            std::cout << "] " << std::endl;

        }

    };
};

int main(){
    int content1[] = {1, 1, 1, 1};
    int content2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    Matrix matrix1(content1, 2, 2);
    Matrix matrix2(content2, 3, 3);
    Matrix matrix3 = matrix1 + matrix2;
    matrix3.print_matrix();
    return 0;
} 