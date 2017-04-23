package firstga;

/**
 *
 * @author diego
 */
import java.util.Random;

public class FirstGA {
   //parar contador cuando todos hayan convergido 
   // optimizar código :)
    //agregar la conversión d elos datos 
    
    
    public static void main(String[] args) {
      int n=4; // Tamaño de la poblacion
      int val_max =0;
      String[] hijos, aux_nuevaG; 
      int padre,hijo,genes;
      genes=6;//numero de bits
      int generaciones = 10;//generaciones
      aux_nuevaG =new String[n];
      String generacion_n ="";
      
      
      String[] padres = Generar_P(n,genes);
      
      for(int x =0;x<generaciones;x++){
      padres = Revolver(padres);
      hijos = Hijos(padres,genes);
      mutar(hijos);
      
      
      for (int i=0;i<padres.length;i++)
      {
          padre=Integer.parseInt(padres[i],2);
          hijo=Integer.parseInt(hijos[i],2);
          if(F_aptitud(padre)>F_aptitud(hijo)){
              aux_nuevaG[i]=padres[i];
              generacion_n+= padres[i]+" ";
              if(val_max<padre){
                  val_max=padre;
              }
          }else
          {
              aux_nuevaG[i]=hijos[i];
              generacion_n=generacion_n + hijos[i]+" ";
              if(val_max<hijo){
                  val_max=hijo;
              }
          }
      }
      System.out.println(generacion_n);
       padres = aux_nuevaG;
       generacion_n="";
    }
   }
    
public static String[] Revolver(String[] padres)
{   // Abre metodo barajar
    Random numerosAleatorios = new Random();
      for ( int primera = 0; primera < padres.length; primera++ )
           { // Abre for
            int segunda = numerosAleatorios.nextInt(padres.length);
            String temp = padres[primera];
           padres[primera] = padres[segunda];
           padres[segunda] = temp;
            }  // Cierra for
            return padres;
 }   
    
    public static String[] Hijos(String[] padres,int genes){
        String[] arre_hijos = new String[padres.length];
        for(int i=0;i<padres.length/2;i++){
            arre_hijos[i]=padres[i].substring(0, (genes/2))+padres[i+padres.length/2].substring((genes/2), genes);
            arre_hijos[i+padres.length/2]=padres[i+padres.length/2].substring(0, (genes/2))+padres[i].substring((genes/2), genes);
          }
         return arre_hijos;
    }
    
    public static String[] Generar_P(int n, int genes){
         Random  rnd = new Random();
        String[] arre_padre = new String[n];
        for(int i=0;i<n;i++){
            String hijo ="";
           for (int j=0;j<genes;j++){
               int val =rnd.nextInt(2);
               hijo +=(val+"");
           }
           
           arre_padre[i]=hijo;
        }
        
        
        return arre_padre;
    }
    
    public static int F_aptitud(int val){
        return val*val;
    }
    
    public static void mutar(String arr[]){
    Random rdn = new Random();
    //Recorremos todo el arreglo
    for(int i=0;i<arr.length;i++){
        // Realizamos dos mutaciones por cadena
        for(int j = 0; j<2;j++){
            int moneda = rdn.nextInt(100);
            // numero de 0 a 100 para tomar de decision de mutacion
            if(moneda < 50){
                //Hacemos una copia de la cadena a mutar
                String mutado = arr[i];
                //Aleatoriamente la posicion de la cadena a mutar
                int pos = rdn.nextInt(mutado.length());
                arr[i] = cambiar(mutado,pos);
            }
        }
        
    }    
    }
    
    public static String cambiar(String cadena,int posicion){
            String binario = ""; 
            int conta =0;
            while(conta < cadena.length()){
                if(conta != posicion){
                binario = binario + cadena.charAt(conta);
                }else{
                    if(cadena.charAt(posicion) == '0'){
                        binario = binario + "1";
                    }else{
                        binario = binario + "0";
                    }
                }
                conta++;
            }
            return binario;
    }
    
}
