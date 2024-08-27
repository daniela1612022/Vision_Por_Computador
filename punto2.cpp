#include <iostream>
#include <opencv2/opencv.hpp>

// Incluye las bibliotecas estándar de C++ y OpenCV necesarias para el procesamiento de imágenes.

int main(int argc, char** argv)
{
    // Cargar la imagen de entrada
    cv::Mat src = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/lena.png");

    // Se carga la imagen de entrada desde la ruta especificada utilizando la función imread.
    // cv::Mat es la clase matriz de OpenCV que almacena imágenes.

    // Verificar que la imagen se cargó correctamente
    if (src.empty()) {
        std::cerr << "Error al cargar la imagen: Ruta incorrecta o archivo no encontrado" << std::endl;
        return -1;
    }

    // Se verifica si la imagen no se cargó correctamente (es decir, si está vacía).
    // Si la imagen no se carga, se imprime un mensaje de error y el programa termina.

    // Mostrar la imagen original en una ventana separada
    cv::imshow("Imagen Original", src);

    // Crear una copia de la imagen original para modificarla
    cv::Mat grayImage = src.clone();

    // Se crea una copia de la imagen original para trabajar sobre ella sin modificar la original.

    // Definir la región de interés (ROI) de 320x320 píxeles
    int x = 100;
    int y = 100;
    int w = 320; // Ancho de la región de interés (320 píxeles)
    int h = 320; // Altura de la región de interés (320 píxeles)

    // Se definen las coordenadas y el tamaño de la región de interés (ROI).
    // La ROI es un área específica de la imagen en la que se aplicarán modificaciones.

    // Crear la ROI (Región de Interés)
    cv::Mat roi = grayImage(cv::Rect(x, y, w, h));

    // Se crea la región de interés dentro de la imagen copiada utilizando las coordenadas y el tamaño definidos.

    // Convertir la ROI a escala de grises
    // Este bucle recorre cada fila de píxeles en la región de interés (roi)
    for (int i = 0; i < roi.rows; i++)
    {

        //cv::Vec3b es un tipo de dato de OpenCV que representa un vector de 3 bytes, es decir,
        //los valores de los canales B, G y R de un píxel en una imagen en color.
        cv::Vec3b* imgrow = roi.ptr<cv::Vec3b>(i);


        // ste bucle recorre cada columna de la fila i.
        // La variable j se incrementa desde 0 hasta roi.cols - 1, donde roi.cols es el número de columnas en la ROI.
        for (int j = 0; j < roi.cols; j++)
        {
            // imgrow[j] da acceso al píxel en la columna j de la fila i.

            uchar B = imgrow[j][0]; //  son los valores de los canales (B,G,R)
            uchar G = imgrow[j][1];
            uchar R = imgrow[j][2];

            // Calcular el valor de gris
            // Para convertir el píxel de color a escala de grises,
            // se promedian los valores de los tres canales (B, G y R). Este promedio es el valor de gris.
            uchar gray = (B + G + R) / 3;

            // Asignar el valor de gris a cada canal (B, G, R)
            // Esto convierte efectivamente el píxel en un tono de gris.
            imgrow[j][0] = gray;
            imgrow[j][1] = gray;
            imgrow[j][2] = gray;
        }
    }

    // Se recorre cada píxel de la ROI.
    // Se obtiene el valor de cada canal de color (B, G, R) y se calcula el valor de gris promedio.
    // Luego, se asigna este valor de gris a cada canal de color, convirtiendo así la región a escala de grises.

    // Mostrar la imagen en escala de grises
    cv::imshow("Imagen en Escala de Grises", grayImage);

    // Crear una copia para la binarización
    cv::Mat binaryImage = grayImage.clone();

    // Se crea una copia de la imagen en escala de grises para aplicar la binarización.

    // Binarizar la ROI con un umbral de 127
    // cv::threshold es una función de OpenCV que aplica una operación de umbralización (binarización) a una imagen.
    // 127 es el valor de umbral. Esto significa que cualquier píxel con un valor de intensidad por debajo de 127
    // se convertirá en 0 (negro), y cualquier píxel con un valor igual o superior a 127 se convertirá en 255 (blanco).

    cv::Mat roiBinary = binaryImage(cv::Rect(x, y, w, h));
    cv::threshold(roiBinary, roiBinary, 127, 255, cv::THRESH_BINARY);

    // cv::THRESH_BINARY indica el tipo de umbralización.
    // Se selecciona la misma región de interés (ROI) en la imagen en escala de grises.
    // Se aplica una binarización a la ROI con un umbral de 127, donde los valores por encima del umbral se establecen en 255 (blanco) y los valores por debajo en 0 (negro).

    // Mostrar la imagen binarizada
    cv::imshow("Imagen Binarizada", binaryImage);

    // Se muestra la imagen con la región binarizada en una nueva ventana con el título "Imagen Binarizada".

    // Esperar a que se presione una tecla para cerrar
    cv::waitKey(0);

    // El programa espera a que se presione una tecla antes de cerrar todas las ventanas y finalizar.

    return 0;
}
