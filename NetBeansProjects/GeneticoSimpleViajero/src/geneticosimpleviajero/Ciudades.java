package geneticosimpleviajero;
import java.util.Random;
/**
 *
 * @author alejandro
 */
public class Ciudades{
  private static final String ciudades = "abcdefghij";
  private static final int distancias[][] = {
    {0,20,15,30,25,40,30,60,50,95},
    {20,0,30,20,15,15,20,40,40,30},
    {15,30,0,25,30,20,30,40,45,50},
    {30,20,25,0,20,30,10,50,40,30},
    {25,15,30,20,0,10,20,20,30,40},
    {40,15,20,30,10,0,20,30,20,30},
    {30,20,30,10,20,20,0,25,40,30},
    {60,40,40,50,20,30,25,0,30,15},
    {50,40,45,40,30,20,40,30,0,20},
    {95,30,50,30,40,30,30,15,20,0}
  };

  public static int distanciasXY(char x, char y){
    int i = ciudades.indexOf(x);
    int j = ciudades.indexOf(y);
    return distancias[i][j];
  }

  public static char getCiudad(int id){
    return ciudades.charAt(id);
  }
}


