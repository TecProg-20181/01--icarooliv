#include <stdio.h>

typedef struct _pixel {
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
} Pixel;

typedef struct _image {
    unsigned short int pixel[512][512][3];
    unsigned int width;
    unsigned int height;
} Image;

Image grayscale(Image img) {
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            int media = img.pixel[i][j][0] +
                        img.pixel[i][j][1] +
                        img.pixel[i][j][2];
            media /= 3;
            img.pixel[i][j][0] = media;
            img.pixel[i][j][1] = media;
            img.pixel[i][j][2] = media;
        }
    }

    return img;
}

Image blur(unsigned int height, unsigned short int pixel [512][512][3], unsigned int width) {
    int size = 0;
    scanf("%d", &size);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            Pixel media = {0, 0, 0};

            int min_h = (height - 1 > i + size/2) ? i + size/2 : height - 1;
            int min_w = (width - 1 > j + size/2) ? j + size/2 : width - 1;
            for(int x = (0 > i - size/2 ? 0 : i - size/2); x <= min_h; ++x) {
                for(int y = (0 > j - size/2 ? 0 : j - size/2); y <= min_w; ++y) {
                    media.r += pixel[x][y][0];
                    media.g += pixel[x][y][1];
                    media.b += pixel[x][y][2];
                }
            }
            media.r /= size * size;
            media.g /= size * size;
            media.b /= size * size;

            pixel[i][j][0] = media.r;
            pixel[i][j][1] = media.g;
            pixel[i][j][2] = media.b;
        }
    }
}

Image rotacionar90direita(Image img) {
    Image rotacionada;
    
    rotacionada.width = img.height;
    rotacionada.width = img.width;

    for (unsigned int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
        for (int j = rotacionada.width - 1, x = 0; j >= 0; --j, ++x) {
            rotacionada.pixel[i][j][0] = img.pixel[x][y][0];
            rotacionada.pixel[i][j][1] = img.pixel[x][y][1];
            rotacionada.pixel[i][j][2] = img.pixel[x][y][2];
        }
    }
    
    return rotacionada;
}

void inverter_cores(unsigned short int pixel[512][512][3],
                    unsigned int w, unsigned int h) {
    for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            pixel[i][j][0] = 255 - pixel[i][j][0];
            pixel[i][j][1] = 255 - pixel[i][j][1];
            pixel[i][j][2] = 255 - pixel[i][j][2];
        }
    }
}

Image cut_image(Image img, int x, int y, int w, int h) {
    Image cortada;

    cortada.width = w;
    cortada.height = h;

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            cortada.pixel[i][j][0] = img.pixel[i + y][j + x][0];
            cortada.pixel[i][j][1] = img.pixel[i + y][j + x][1];
            cortada.pixel[i][j][2] = img.pixel[i + y][j + x][2];
        }
    }
    return cortada;
}

Image sepia(Image img){
    Image img_filtrada;
    for (unsigned int x = 0; x < img.height; ++x) {
        for (unsigned int j = 0; j < img.width; ++j) {
            unsigned short int pixel[3];
            pixel[0] = img.pixel[x][j][0];
            pixel[1] = img.pixel[x][j][1];
            pixel[2] = img.pixel[x][j][2];

            int p =  pixel[0] * .393 + pixel[1] * .769 + pixel[2] * .189;
            int menor_r = (255 >  p) ? p : 255;
            img.pixel[x][j][0] = menor_r;

            p =  pixel[0] * .349 + pixel[1] * .686 + pixel[2] * .168;
            menor_r = (255 >  p) ? p : 255;
            img.pixel[x][j][1] = menor_r;

            p =  pixel[0] * .272 + pixel[1] * .534 + pixel[2] * .131;
            menor_r = (255 >  p) ? p : 255;
            img.pixel[x][j][2] = menor_r;
        }
    }
return img;

}

Image invert (Image img){
        int horizontal = 0;
        scanf("%d", &horizontal);

        int w = img.width;
        int h = img.height;

        if (horizontal == 1) w /= 2;
        else h /= 2;

        for (int i2 = 0; i2 < h; ++i2) {
            for (int j = 0; j < w; ++j) {
            int x = i2, y = j;

            if (horizontal == 1) y = img.width - 1 - j;
            else x = img.height - 1 - i2;

            Pixel aux1;
            aux1.r = img.pixel[i2][j][0];
            aux1.g = img.pixel[i2][j][1];
            aux1.b = img.pixel[i2][j][2];

            img.pixel[i2][j][0] = img.pixel[x][y][0];
            img.pixel[i2][j][1] = img.pixel[x][y][1];
            img.pixel[i2][j][2] = img.pixel[x][y][2];

            img.pixel[x][y][0] = aux1.r;
            img.pixel[x][y][1] = aux1.g;
            img.pixel[x][y][2] = aux1.b;
            }
        }
return img;
}

int main() {
    Image img;

    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &img.width, &img.height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            scanf("%hu %hu %hu", &img.pixel[i][j][0],
                                 &img.pixel[i][j][1],
                                 &img.pixel[i][j][2]);
        }
    }
    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) {
        int opcao;
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: { // Escala de Cinza
                img = grayscale(img);
                break;
            }
            case 2: { // Filtro Sepia
                img = sepia(img);
                break;
            }
            case 3: { // Blur
                blur(img.height, img.pixel, img.width);    
                break;
            }
            case 4: { // Rotacao
                int quantas_vezes = 0;
                scanf("%d", &quantas_vezes);
                quantas_vezes %= 4;
                for (int j = 0; j < quantas_vezes; ++j) {
                    img = rotacionar90direita(img);
                }
                break;
            }
            case 5: { // Espelhamento
                img = invert(img);
                break;
            }

            case 6: { // Inversao de Cores
                inverter_cores(img.pixel, img.width, img.height);
                break;
            }
            case 7: { // Cortar Imagem
                int x, y;
                scanf("%d %d", &x, &y);
                int w, h;
                scanf("%d %d", &w, &h);
                img = cut_image(img, x, y, w, h);
                break;
            }
        }
    }

    // print type of image
    printf("P3\n");
    // print width height and color of image
    printf("%u %u\n255\n", img.width, img.height);
    // print pixels of image
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            printf("%hu %hu %hu ", img.pixel[i][j][0],
                                   img.pixel[i][j][1],
                                   img.pixel[i][j][2]);
        }
        printf("\n");
    }
    return 0;
}