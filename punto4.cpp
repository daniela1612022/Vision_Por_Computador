#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv)
{
    // Cargar las imágenes (a) y (b)
    cv::Mat imgA = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/imA.bmp", cv::IMREAD_GRAYSCALE);
    cv::Mat imgB = cv::imread("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/imB.png", cv::IMREAD_GRAYSCALE);

    // Verificar que las imágenes se cargaron correctamente
    if (imgA.empty() || imgB.empty()) {
        std::cerr << "Error al cargar las imágenes: Verifique las rutas de los archivos" << std::endl;
        return -1;
    }

    // Realizar la sustracción de las imágenes para obtener la diferencia
    cv::Mat diff;
    cv::absdiff(imgA, imgB, diff);

    // Mejorar el contraste de la imagen de diferencia
    cv::Mat enhanced_diff;
    cv::normalize(diff, enhanced_diff, 0, 255, cv::NORM_MINMAX);

    // Umbralizar la imagen para crear una máscara que resalte solo el triceratops
    cv::Mat mask;
    cv::threshold(enhanced_diff, mask, 50, 255, cv::THRESH_BINARY);

    // Limpiar la máscara con operaciones morfológicas
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, kernel);

    // Invertir la máscara para afectar solo el fondo
    cv::Mat mask_invertida;
    cv::bitwise_not(mask, mask_invertida);

    // Aumentar mucho el brillo y reducir drásticamente el contraste del fondo
    cv::Mat imgA_lightened = imgA.clone();
    imgA_lightened.convertTo(imgA_lightened, -1, 0.5, 220); // Reducir el contraste y aumentar el brillo

    // Combinar la imagen con fondo extremadamente aclarado con la imagen original usando la máscara
    cv::Mat result = imgA_lightened.clone();  // Iniciar con la imagen de fondo aclarado
    imgA.copyTo(result, mask);  // Restaurar el triceratops original en la imagen aclarada

    // Guardar la imagen resultante
    cv::imwrite("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/resultado_triceratops_fondo_extremadamente_claro.png", result);

    // Encontrar los contornos en la máscara para aislar el triceratops
    std::vector<std::vector<cv::Point>> contornos;
    cv::findContours(mask, contornos, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Suponer que el triceratops es el contorno más grande
    int maxAreaIndex = 0;
    double maxArea = cv::contourArea(contornos[0]);
    for (size_t i = 1; i < contornos.size(); i++) {
        double area = cv::contourArea(contornos[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaIndex = i;
        }
    }

    // Obtener la caja englobante (bounding box) del triceratops
    cv::Rect boundingBox = cv::boundingRect(contornos[maxAreaIndex]);

    // Calcular el centro de la bounding box
    cv::Point center;
    center.x = boundingBox.x + boundingBox.width / 2;
    center.y = boundingBox.y + boundingBox.height / 2;

    // Dibujar la bounding box y el centro en la imagen resultante
    cv::Mat finalResult = result.clone();
    cv::rectangle(finalResult, boundingBox, cv::Scalar(0, 0, 0), 2); // Dibujar la bounding box en negro
    cv::circle(finalResult, center, 5, cv::Scalar(0, 0, 0), -1); // Marcar el centro en negro

    // Mostrar la posición (x, y) del centro de masa en la consola
    std::cout << "Centro de masa del triceratops: (" << center.x << ", " << center.y << ")" << std::endl;

    // Mostrar la imagen con el triceratops aislado
    cv::imshow("Imagen del Triceratops con Fondo Muy Lavado", result);

    // Mostrar la imagen resultante con la bounding box y el centro
    cv::imshow("Bounding Box y Centro de Masa", finalResult);

    // Guardar la imagen resultante con la bounding box y el centro
    cv::imwrite("/home/dani/Downloads/Vision_Por_Computador/Taller_Vison_1/Images/resultado_bounding_box.png", finalResult);

    // Esperar a que se presione una tecla para cerrar
    cv::waitKey(0);

    return 0;
}
