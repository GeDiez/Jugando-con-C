/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package imagen;
import java.awt.Color;
import java.awt.image.BufferedImage;
import static java.awt.image.BufferedImage.TYPE_INT_RGB;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

/**
 *
 * @author Luis
 */
public class ProcesamientoImagen {
    
    //Imagen actual que se ha cargado
    private BufferedImage imageActual,imagenGris,imagenBinario;
    int arr[][];
    
    //Método que devuelve una imagen abierta desde archivo
    //Retorna un objeto BufferedImagen
    public BufferedImage abrirImagen(){
        //Creamos la variable que será devuelta (la creamos como null)
        BufferedImage bmp=null;
        //Creamos un nuevo cuadro de diálogo para seleccionar imagen
        JFileChooser selector=new JFileChooser();
        //Le damos un título
        selector.setDialogTitle("Seleccione una imagen");
        //Filtramos los tipos de archivos
        FileNameExtensionFilter filtroImagen = new FileNameExtensionFilter("JPG & GIF & BMP", "jpg", "gif", "bmp");
        selector.setFileFilter(filtroImagen);
        //Abrimos el cuadro de diálog
        int flag=selector.showOpenDialog(null);
        //Comprobamos que pulse en aceptar
        if(flag==JFileChooser.APPROVE_OPTION){
            try {
                //Devuelve el fichero seleccionado
                File imagenSeleccionada=selector.getSelectedFile();
                //Asignamos a la variable bmp la imagen leida
                bmp = ImageIO.read(imagenSeleccionada);
            } catch (Exception e) {
            }
                 
        }
        //Asignamos la imagen cargada a la propiedad imageActual
        imageActual=bmp;
        //Retornamos el valor
        return bmp;
    }
    public BufferedImage original(){
        return imageActual;
    
    }
    
    public BufferedImage escalaGrises(){
        imagenGris=new BufferedImage(imageActual.getWidth(),imageActual.getHeight(),TYPE_INT_RGB);
        //Variables que almacenarán los píxeles
        int mediaPixel,colorSRGB;
        Color colorAux;
                
        //Recorremos la imagen píxel a píxel
        for( int i = 0; i < imageActual.getWidth(); i++ ){
            for( int j = 0; j < imageActual.getHeight(); j++ ){
                //Almacenamos el color del píxel
                colorAux=new Color(imageActual.getRGB(i, j));
                //Calculamos la media de los tres canales (rojo, verde, azul)
                mediaPixel=(int)((colorAux.getRed()+colorAux.getGreen()+colorAux.getBlue())/3);
                //Cambiamos a formato sRGB
                colorSRGB=(mediaPixel << 16) | (mediaPixel << 8) | mediaPixel;
                //Asignamos el nuevo valor al BufferedImage
                imagenGris.setRGB(i, j,colorSRGB);
            }
        }
        //Retornamos la imagen
        return imagenGris;
    }
    public BufferedImage Binario(){
        //int umbral=210;
        arr=new int[imageActual.getWidth()][imageActual.getHeight()];
        int umbral = Integer.parseInt(JOptionPane.showInputDialog("Ingrese el umbral: "));
        imagenBinario=new BufferedImage(imageActual.getWidth(),imageActual.getHeight(),TYPE_INT_RGB);
        //Variables que almacenarán los píxeles
        int mediaPixel,colorSRGB;
        Color colorAux;
                
        //Recorremos la imagen píxel a píxel
        for( int i = 0; i < imageActual.getWidth(); i++ ){
            for( int j = 0; j < imageActual.getHeight(); j++ ){
                //Almacenamos el color del píxel
                colorAux=new Color(imageActual.getRGB(i, j));
                //Calculamos la media de los tres canales (rojo, verde, azul)
                mediaPixel=(int)((colorAux.getRed()+colorAux.getGreen()+colorAux.getBlue())/3);
                //Cambiamos a formato sRGB
                if(mediaPixel<umbral){
                    mediaPixel=0;
                    arr[i][j]=0;
                }
                else{
                    mediaPixel=255;
                    arr[i][j]=1;
                }
                colorSRGB=(mediaPixel << 16) | (mediaPixel << 8) | mediaPixel;
                //Asignamos el nuevo valor al BufferedImage
                imagenBinario.setRGB(i, j,colorSRGB);
            }
        }
        //Retornamos la imagen
        return imagenBinario;
    }
     
    public int[] histograma(){
        int[] histo=new int[257];
        for(int i=0;i<257;i++){
            histo[i]=0;
        }
        BufferedImage auxImg=imageActual;
        //Variables que almacenarán los píxeles
        int mediaPixel,colorSRGB;
        Color colorAux;
        //Recorremos la imagen píxel a píxel
        for( int i = 0; i < auxImg.getWidth(); i++ ){
            for( int j = 0; j < auxImg.getHeight(); j++ ){
                //Almacenamos el color del píxel
                colorAux=new Color(auxImg.getRGB(i, j));
                //Calculamos la media de los tres canales (rojo, verde, azul)
                mediaPixel=(int)((colorAux.getRed()+colorAux.getGreen()+colorAux.getBlue())/3);
                //System.out.println(mediaPixel);
                histo[mediaPixel]++;
                
                //Cambiamos a formato sRGB
               // colorSRGB=(mediaPixel << 16) | (mediaPixel << 8) | mediaPixel;
                //Asignamos el nuevo valor al BufferedImage
               // auxImg.setRGB(i, j,colorSRGB);
            }
        }
        //Retornamos la imagen
        return histo;
    }
    public int NUmObjetos(){
        int etiqueta=2;
        for(int i=0;i<imageActual.getWidth();i++){
            for(int j=0;j<imageActual.getHeight();j++){
                if(arr[i][j]!=0){
                    if(HayVecinos(i,j)!=0){
                     arr[i][j]=HayVecinos(i,j);                     
                    }
                    else{
                        arr[i][j]=etiqueta;
                        etiqueta++;
                    }
                    
                }
                //arr[i][j]
                System.out.print(arr[i][j]);
            }
            System.out.println("");
        }
        for(int i=0;i<imageActual.getWidth();i++){
            for(int j=0;j<imageActual.getHeight();j++){
                
            }
        }
        return etiqueta-2;
    }

    public int HayVecinos(int i,int j){
        int aux=0;
        if(i>0){
            if(arr[i-1][j]!=0){
                aux=arr[i-1][j];
            }
        }        
        else if(j>0){
            if(arr[i][j-1]!=0){
                aux=arr[i][j-1];
            }
            if(arr[i][j-1]!=0){
                aux=arr[i][j-1];
            }
        }
        else if(j>0 && i>0){
           if(arr[i-1][j-1]!=0){
                aux=arr[i-1][j-1];
            }
        }
        else if(j>0 & i<imageActual.getWidth()){
            if(arr[i+1][j-1]!=0){
                aux=arr[i-1][j-1];
            }
        }
        
    return aux;
    }
    
}
