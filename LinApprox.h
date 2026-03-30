//ver 1 - версия файла
#include "math.h"

// Шаблонный класс для линейной регрессии с N переменными
// Уравнение: y = coeffs[0]*x[0] + coeffs[1]*x[1] + ... + coeffs[N-1]*x[N-1]
template<int N>
class LinApprox
{
public:
    LinApprox() { Clear(); }
    
    void Clear()
    {
        for (int i = 0; i < N*N; i++) matrix_A[i] = 0;
        for (int i = 0; i < N; i++) matrix_B[i] = 0;
        for (int i = 0; i < N; i++) result[i] = 0;
    }
    
    // Добавить одну точку данных
    // x[] — массив из N аргументов, y — целевое значение
    void Add(double y, const double* x)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                matrix_A[i + j * N] += x[i] * x[j];
            }
            matrix_B[i] += x[i] * y;
        }
    }
    
    // Рассчитать коэффициенты, результат в outCoeffs[N]
    void Calc(double* outCoeffs)
    {
        GaussianElimination(matrix_A, matrix_B, result);
        for (int i = 0; i < N; i++) outCoeffs[i] = result[i];
    }
    
    // Прямой доступ к результату (опционально)
    const double* GetResult() const { return result; }
    
private:
    double matrix_A[N * N];  // Матрица нормальных уравнений (столбцово-ориентированная)
    double matrix_B[N];      // Вектор правых частей
    double result[N];        // Искомые коэффициенты
    
    // Метод Гаусса с выбором главного элемента
    static void GaussianElimination(double* _matrixA, double* _vectorB, double* result)
    {
        int n=N;
        double matrixA[n * n];
        double vectorB[n];
        for (int i = 0; i < n * n; i++)
        {
            matrixA[i] = _matrixA[i];
        }
        for (int i = 0; i < n; i++)
        {
            vectorB[i] = _vectorB[i];
        }
        for (int i = 0; i < n; i++)
        {
            // Поиск максимального элемента в столбце
            double maxElement = fabs(matrixA[i + i * n]);
            int maxIndex = i;
            for (int k = i + 1; k < n; k++)
            {
                if (fabs(matrixA[k + i * n]) > maxElement)
                {
                    maxElement = fabs(matrixA[k + i * n]);
                    maxIndex = k;
                }
            }
            // Перестановка строк
            for (int k = i; k < n; k++)
            {
                double temp = matrixA[i + k * n];
                matrixA[i + k * n] = matrixA[maxIndex + k * n];
                matrixA[maxIndex + k * n] = temp;
            }
            double tempB = vectorB[i];
            vectorB[i] = vectorB[maxIndex];
            vectorB[maxIndex] = tempB;
            // Приведение матрицы к верхнетреугольному виду
            for (int k = i + 1; k < n; k++)
            {
                double factor = matrixA[k + i * n] / matrixA[i + i * n];
                vectorB[k] -= factor * vectorB[i];
                for (int j = i; j < n; j++)
                {
                    matrixA[k + j * n] -= factor * matrixA[i + j * n];
                }
            }
        }
        // Обратный ход метода Гаусса
        for (int i = n - 1; i >= 0; i--)
        {
            result[i] = vectorB[i];
            for (int j = i + 1; j < n; j++)
            {
                result[i] -= matrixA[i + j * n] * result[j];
            }
            result[i] /= matrixA[i + i * n];
        }
    }
};

// Обёртка для удобного использования с 4 переменными, y = a*x1+b*x2*c*x3*d*x4
class LinApprox4 : public LinApprox<4>
{
public:
    void Add(double y, double x1, double x2, double x3, double x4)
    {
        double x[4] = {x1, x2, x3, x4};
        LinApprox<4>::Add(y, x);
    }
    
    void Calc(double& A, double& B, double& C, double& D)
    {
        double coeffs[4];
        LinApprox<4>::Calc(coeffs);
        A = coeffs[0];
        B = coeffs[1];
        C = coeffs[2];
        D = coeffs[3];
    }
};
