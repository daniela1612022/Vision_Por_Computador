#include <opencv2/opencv.hpp>

// Este es el archivo de cabecera principal de OpenCV que incluye todas las funciones y clases necesarias.

int main() {
    // Cargar las 6 imágenes
    cv::Mat img1 = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/image1.jpg");
    cv::Mat img2 = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/image2.jpg");
    cv::Mat img3 = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/image3.jpg");
    cv::Mat img4 = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/image4.jpg");
    cv::Mat img5 = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/image5.jpg");
    cv::Mat img6 = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/image6.jpg");

    // Se cargan 6 imágenes desde el disco duro utilizando la función imread.
    // cv::Mat es la clase matriz de OpenCV que almacena imágenes.

    // Verificar que las imágenes se cargaron correctamente
    if (img1.empty() || img2.empty() || img3.empty() || img4.empty() || img5.empty() || img6.empty()) {
        std::cerr << "Error al cargar una o más imágenes" << std::endl;
        return -1;
    }

    // Se verifica si alguna de las imágenes no se cargó correctamente (es decir, si está vacía).
    // Si alguna imagen no se carga, se imprime un mensaje de error y el programa termina.

    // Redimensionar todas las imágenes a un tamaño común
    cv::Size size(400, 400); // Ancho , Largo
    cv::resize(img1, img1, size);
    cv::resize(img2, img2, size);
    cv::resize(img3, img3, size);
    cv::resize(img4, img4, size);
    cv::resize(img5, img5, size);
    cv::resize(img6, img6, size);

    // Todas las imágenes se redimensionan a un tamaño común de 400x400 píxeles utilizando la función resize.
    // Esto es necesario para que todas las imágenes tengan el mismo tamaño cuando se combinen en una sola imagen.

    // Crear una imagen grande para contener las 6 imágenes
    int rows = size.height * 2; // 2 filas
    int cols = size.width * 3;   // 3 columnas
    cv::Mat displayImg(rows, cols, img1.type());

    // Se crea una imagen grande (displayImg) que contendrá las 6 imágenes.
    // Las dimensiones de la imagen grande son de 2 filas y 3 columnas, cada celda tiene un tamaño de 400x400 píxeles.
    // Se utiliza el tipo de la primera imagen (img1.type()) para definir el tipo de la imagen grande.

    // Copiar las imágenes a la imagen grande
    img1.copyTo(displayImg(cv::Rect(0, 0, size.width, size.height)));
    img2.copyTo(displayImg(cv::Rect(size.width, 0, size.width, size.height)));
    img3.copyTo(displayImg(cv::Rect(2 * size.width, 0, size.width, size.height)));
    img4.copyTo(displayImg(cv::Rect(0, size.height, size.width, size.height)));
    img5.copyTo(displayImg(cv::Rect(size.width, size.height, size.width, size.height)));
    img6.copyTo(displayImg(cv::Rect(2 * size.width, size.height, size.width, size.height)));

    // Se copian las imágenes redimensionadas a la imagen grande en posiciones específicas.
    // cv::Rect define la región (rectángulo) en la que se copia cada imagen dentro de displayImg.
    // La primera imagen se coloca en la esquina superior izquierda (0, 0),
    // la segunda en la columna siguiente, y así sucesivamente.

    // Mostrar la imagen grande
    cv::imshow("Imagenes en una Ventana", displayImg);

    // Se muestra la imagen grande que contiene las 6 imágenes en una ventana con el título "Imagenes en una Ventana".

    // Esperar a que se presione una tecla para cerrar
    cv::waitKey(0);
    return 0;
}

