#include <iostream>
#include <cassert>


class Matrix{
    private:
        size_t rows;
        size_t cols;
        double* matrix_content; 
        int matrix_size = rows * cols;
    public:
    
        size_t get_rows() const {return rows;}
        size_t get_cols() const {return cols;}
        double at(size_t index) const {return matrix_content[index];}

        Matrix(size_t rows, size_t cols){
            this->rows = rows;
            this->cols = cols;
            this->matrix_size = rows * cols;
            this->matrix_content = new double[matrix_size];
        }
        
        template <size_t N>
        Matrix(double(&arr)[N], size_t row, size_t col){
            this->rows = row;
            this->cols = col;
            matrix_size = rows * cols;
            matrix_content = new double[matrix_size];
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
            this->matrix_content = new double[matrix_size];
            for(size_t i{0}; i < matrix_size; ++i){
                this->matrix_content[i] = other.matrix_content[i];
            }
        }

        Matrix& operator=(const Matrix& other){
            if(this == &other){
                return *this;
            }
            this->matrix_size = other.matrix_size;
            double* old_content = this->matrix_content;
            this->matrix_content = new double[matrix_size];
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
        Matrix operator-(const Matrix& other) const{
            assert(other.rows == this->rows);
            assert(other.cols == this->cols);
            Matrix result(rows, cols);
            for(size_t i{0}; i <= rows-1; i++){
                for(size_t j{0};  j <= cols-1; j++){
                    size_t index = i * cols + j;
                    result.matrix_content[index] = this->matrix_content[index] - other.matrix_content[index];
                }
            }
            return(result);
        }
        Matrix operator*(const double scalar) const{
            Matrix result(this->rows, this->cols);

            for(size_t i{0}; i <= rows - 1; ++i){
                for(size_t j{0}; j <= cols -1; ++j){
                    size_t index = i * cols + j;
                    result.matrix_content[index] = this->matrix_content[index] * scalar;
                }    
            }
            return result;
        }
        void operator*=(const double scalar) const{
            for(size_t i{0}; i <= rows - 1; ++i){
                for(size_t j{0}; j <= cols -1; ++j){
                    size_t index = i * cols + j;
                    this->matrix_content[index] = this->matrix_content[index] * scalar;
                }    
            }
        }

        Matrix operator*(const Matrix& other) const{
            assert(this->cols == other.rows);
            Matrix result(this->rows, other.cols);
            for(size_t i{0}; i <= result.rows - 1; ++i){
                for(size_t j{0}; j<= result.cols - 1; ++j){
                    double sum = 0;
                    for(size_t k{0}; k < this->cols; ++k){
                        sum += (this->matrix_content[(i * this->cols + k)] * other.matrix_content[k * other.cols + j]);
                    }
                    size_t result_index = i * result.cols + j;
                    result.matrix_content[result_index] = sum;
                }
            }
            return result;
        }
        Matrix transpose(){
            Matrix result(this->cols, this->rows);
            for(size_t i{0}; i <= this->rows - 1; ++i){
                for(size_t j{0}; j <= this->cols - 1; ++j){
                    size_t start_index = i * this->cols + j;
                    size_t end_index = j * result.cols + i;
                    result.matrix_content[end_index] = this->matrix_content[start_index];      
                }
            }
            return result;
        }
};


std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
        for(size_t i{0}; i <= matrix.get_rows() - 1; ++i){
            os << "[";
            for(size_t j{0}; j <= matrix.get_cols() - 1; ++j){
                size_t element_index = i * matrix.get_cols() + j;
                if(!(j == 0)){
                    os << ", ";
                }
                os << matrix.at(element_index);
            }
            os  << "] " << "\n";
        }
        return os;
    }

int main(){
    double content1[] = {2, 2, 2, 2};
double content2[] = {1, 2, 3, 4, 5, 6};
    Matrix matrix1(content1, 2, 2);
    Matrix matrix2(content2, 2, 3);
    Matrix matrix3 = matrix2.transpose();
    std::cout << matrix2 << "\n" << matrix3;
    return 0;
} 