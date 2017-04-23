
package viajeroga;
import java.util.Random;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartFrame;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public class ViajeroGA {
    static int [][]  rutas = {
                      {0,20,15,30,25,40,30,60,50,95},
                      {20,0,30,20,15,15,20,40,40,30},
                      {15,30,0,25,30,20,30,40,45,50},
                      {30,20,25,0,20,30,10,50,40,80},
                      {25,15,30,20,0,10,20,20,30,40},
                      {40,15,20,30,10,0,20,30,20,30},
                      {30,20,30,10,20,20,0,25,40,30},
                      {60,40,40,50,20,30,25,0,30,15},
                      {50,40,45,40,30,20,40,30,0,20},
                      {95,30,50,80,40,30,30,15,20,0}
                     };

    public static void main(String[] args) {
        int generaciones = 150; //INGRESAR NUMERO DE GENERACIOMES
        char letra_inicio = 'a'; // CIUDAD EN LA QUE SE VA A INICIAR
        int poblacion = 100; // POBLACION CON LA QUE SE ESTARÁ TRABAJANDO
        String[] hijos, aux_nuevaG; 
        aux_nuevaG = new String[poblacion];
        int[] aux_mejor = new int[generaciones];
        
        String[] padres =Generar_P(letra_inicio,poblacion);
        for(int x =0;x<generaciones;x++){
            aux_mejor[x]= El_mejor(padres);
            padres = Revolver(padres);
            hijos = Hijos(padres);
            Mutar(hijos);
            for (int i=0;i<padres.length;i++){
                 aux_nuevaG[i]=F_aptitud(padres[i],hijos[i]);                
            }
            padres =aux_nuevaG;
        }
        
        M_grafica(aux_mejor);
    }
        public static String[] Generar_P(char letra_i,int ite){ //letra_i = letra de inicio y ite = tamaño de la población
         String[] salida = new String[ite];
         Random  rnd = new Random();
         String hijo;
         for(int j=0;j<ite;j++){
         char[] arre = {'a','b','c','d','e','f','g','h','i','j'};
         hijo="";
         hijo+=letra_i;
         int segundo;
         char aux;
        for(int i=0;i<arre.length;i++){
            segundo = rnd.nextInt(arre.length);
            aux=arre[i];
            arre[i]=arre[segundo];
            arre[segundo]=aux;
        }
        for(int i=0;i<arre.length;i++){
            if(arre[i]!=letra_i){
                hijo+=arre[i];
            }
        }
        hijo+=letra_i;
        salida[j]=hijo;
         }
        return salida;
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
    
        public static String[] Hijos(String[] padres){
        String[] arre_hijos = new String[padres.length];
       // Random  rnd = new Random();
        String hijo1,hijo2;
        for(int i=0;i<padres.length/2;i++){
        hijo1 = padres[i].substring(0, 6);
        hijo2 = padres[padres.length/2+i].substring(0, 6);
            //hijo1
            for(int j=1;j<10;j++){
                if(hijo1.indexOf(padres[padres.length/2+i].charAt(j))== -1){
                    hijo1+=padres[padres.length/2+i].charAt(j);
                }
            }
           hijo1+=hijo1.charAt(0);
           //hijo2
            for(int j=1;j<10;j++){
                if(hijo2.indexOf(padres[i].charAt(j))== -1){
                    hijo2+=padres[i].charAt(j);
                }
            }
           hijo2+=hijo2.charAt(0);
           
           arre_hijos[i]=hijo1;
           arre_hijos[padres.length/2+i]=hijo2;
        }
         return arre_hijos;
    }
        public static String[] Mutar(String[] arre){
            Random  rnd = new Random();
            for(int i=0;i<arre.length;i++){
                int moneda = rnd.nextInt(100);
                if(moneda<51){
                    char[] tmp = arre[i].toCharArray();
                    int val1 = (int)(rnd.nextDouble()*9 +1);
                    int val2 = (int)(rnd.nextDouble()*9 +1);
                    char aux = tmp[val1];
                    tmp[val1]=tmp[val2];
                    tmp[val2]=aux;
                    arre[i]= new String(tmp);
                }
            }
            return arre;
        }
        public static String F_aptitud(String padre,String hijo){
          String cadena = "abcdefghij";
          int suma_p=0;
          int suma_h=0;
          for(int i=0;i<padre.length()-1;i++){
              suma_p+=rutas[cadena.indexOf(padre.charAt(i))][cadena.indexOf(padre.charAt(i+1))];
              suma_h+=rutas[cadena.indexOf(hijo.charAt(i))][cadena.indexOf(hijo.charAt(i+1))];
          }
          if(suma_p<suma_h){
              return padre;
          }
          else{
              return hijo;
          }
        }
        public static int El_mejor(String[] arre){
        String cadena = "abcdefghij";
        int mejor = 500;
        int suma = 0;
        for (String padre : arre) {
            for(int i=0;i<padre.length()-1;i++){
                suma+=rutas[cadena.indexOf(padre.charAt(i))][cadena.indexOf(padre.charAt(i+1))];
            }
            if(suma<mejor){
                mejor=suma;
            }
            suma=0;
        }
        return mejor;
        }
    public static JFreeChart M_grafica(int arr[]){
    XYSeries series = new XYSeries("Mejores rutas");
        for(int i=0;i<arr.length;i++){
        series.add(i,arr[i]);
        }

        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(series);

        JFreeChart chart = ChartFactory.createXYLineChart("Viajero Algoritmo Genético","Num. Iteraciones","Mejor resultado ",dataset,PlotOrientation.VERTICAL,
        true,false,false);
        ChartFrame frame = new ChartFrame("Grafica Lineal", chart);
        frame.pack();
        frame.setVisible(true);
        return chart;
    }
}


