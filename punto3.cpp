#include <iostream>
#include <opencv2/opencv.hpp>

// Incluye las bibliotecas estándar de C++ y OpenCV necesarias para el procesamiento de imágenes.

int main(int argc, char** argv)
{
    // Cargar las imágenes (a) y (b) en escala de grises
    cv::Mat imgA = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/imA.bmp", cv::IMREAD_GRAYSCALE);
    cv::Mat imgB = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/imB.png", cv::IMREAD_GRAYSCALE);

    // Verificar que las imágenes se cargaron correctamente
    if (imgA.empty() || imgB.empty()) {
        std::cerr << "Error al cargar las imágenes: Verifique las rutas de los archivos" << std::endl;
        return -1;
    }

    // Mostrar las imágenes originales
    cv::imshow("Imagen A", imgA);
    cv::imshow("Imagen B", imgB);

    // Realizar la sustracción de las imágenes
    cv::Mat diff;
    cv::absdiff(imgA, imgB, diff);

    // Se realiza una sustracción absoluta entre las dos imágenes para obtener la diferencia entre ellas.
    // Esto produce una imagen en la que los píxeles que son diferentes entre las dos imágenes son destacados.

    // Mejorar el contraste de la imagen de diferencia
    cv::Mat enhanced_diff;
    cv::normalize(diff, enhanced_diff, 0, 255, cv::NORM_MINMAX);

    // Se normaliza la imagen de diferencia para mejorar el contraste.
    // La función cv::normalize ajusta los valores de píxel en la imagen de salida para que abarquen un rango entre 0 y 255.

    // Aplicar un ligero desenfoque para suavizar la diferencia
    cv::GaussianBlur(enhanced_diff, enhanced_diff, cv::Size(5, 5), 1.5);

    // Se aplica un desenfoque gaussiano para suavizar la imagen y reducir el ruido.
    // Esto ayuda a eliminar pequeñas variaciones que podrían no ser relevantes para la detección de contornos.

    // Mostrar la imagen mejorada sin dibujo de bounding box ni centro de masa
    cv::imshow("Imagen Mejorada", enhanced_diff);

    // Mostrar la imagen mejorada en una ventana sin ningún dibujo adicional (sin bounding box ni centro de masa).

    // Guardar la imagen mejorada sin los dibujos
    cv::imwrite("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/triceratops_sin_dibujos.png", enhanced_diff);

    // Guardar la imagen mejorada sin los dibujos en un archivo en el disco.

    // Convertir la imagen mejorada a color para poder dibujar sobre ella
    cv::Mat imgWithBoundingBox;
    cv::cvtColor(enhanced_diff, imgWithBoundingBox, cv::COLOR_GRAY2BGR);

    // Convertir la imagen mejorada a color (de escala de grises a BGR) para poder dibujar sobre ella.
    // Esto es necesario porque las funciones de dibujo de OpenCV trabajan con imágenes en color.

    // Convertir la imagen mejorada a binaria para facilitar la detección de contornos
    cv::Mat binary_diff;
    cv::threshold(enhanced_diff, binary_diff, 50, 255, cv::THRESH_BINARY);

    // Binarizar la imagen mejorada utilizando un umbral de 50.
    // Los píxeles con un valor superior a 50 se establecen en 255 (blanco) y los inferiores en 0 (negro).
    // Esto facilita la detección de contornos en la imagen.

    // Encontrar los contornos en la imagen binarizada
    std::vector<std::vector<cv::Point>> contornos;
    cv::findContours(binary_diff, contornos, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Detectar los contornos en la imagen binarizada utilizando la función findContours.
    // Se almacenan en un vector de vectores de puntos (contornos).

    // Verificar que se encontraron contornos
    if (contornos.empty()) {
        std::cerr << "No se encontraron contornos en la imagen" << std::endl;
        return -1;
    }

    // Si no se encontraron contornos, se imprime un mensaje de error y el programa termina.

    // Encontrar el contorno más grande (asumimos que es el triceratops)
    int maxAreaIndex = 0;
    double maxArea = cv::contourArea(contornos[0]);
    for (size_t i = 1; i < contornos.size(); i++) {
        double area = cv::contourArea(contornos[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaIndex = i;
        }
    }

    // Recorrer todos los contornos para encontrar el contorno con el área más grande.
    // Se asume que el contorno más grande corresponde al triceratops.
    // Se almacena el índice del contorno más grande en la variable maxAreaIndex.

    // Obtener la caja englobante del contorno más grande
    cv::Rect boundingBox = cv::boundingRect(contornos[maxAreaIndex]);

    // Calcular la caja englobante (bounding box) del contorno más grande.
    // La bounding box es un rectángulo mínimo que contiene todo el contorno.

    // Calcular el centro de la caja englobante
    cv::Point centerOfMass;
    centerOfMass.x = boundingBox.x + boundingBox.width / 2;
    centerOfMass.y = boundingBox.y + boundingBox.height / 2;

    // Calcular el centro de la caja englobante (bounding box).
    // El centro de masa se determina calculando el punto medio de la bounding box.

    // Dibujar la caja englobante y el centro de masa en la imagen
    cv::rectangle(imgWithBoundingBox, boundingBox, cv::Scalar(0, 255, 0), 2);
    cv::circle(imgWithBoundingBox, centerOfMass, 5, cv::Scalar(0, 0, 255), -1);

    // Dibujar la bounding box en verde (cv::Scalar(0, 255, 0)) y el centro de masa en rojo (cv::Scalar(0, 0, 255)).
    // El grosor de la bounding box es de 2 píxeles, y el punto que representa el centro de masa tiene un radio de 5 píxeles.

    // Mostrar la imagen con la caja englobante y el centro de masa
    cv::imshow("Bounding Box y Centro de Masa", imgWithBoundingBox);

    // Mostrar la imagen con la bounding box y el centro de masa en una ventana.

    // Guardar la imagen con la caja englobante y el centro de masa
    cv::imwrite("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/triceratops_bounding_box.png", imgWithBoundingBox);

    // Guardar la imagen resultante con la bounding box y el centro de masa en un archivo en el disco.

    // Esperar a que se presione una tecla para cerrar
    cv::waitKey(0);

    // El programa espera a que se presione una tecla antes de cerrar todas las ventanas y finalizar.

    return 0;
}
