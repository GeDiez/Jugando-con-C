package geneticosimpleviajero;

/**
 *
 * @author alejandro
 */
import java.util.Random;
public class Genotipo implements Cloneable{

  private String genes;
  private int aptitud;

  public Genotipo(String genes){
    this.genes = genes;
    setAptitud();
  }

  public void mutar(boolean muta){
      if(muta){
        int a, b;
        Random rn = new Random();
        do{
          a = (rn.nextInt(genes.length() -2) +1);
          b = (rn.nextInt(genes.length() -2) +1);
        }while(a == b);
        char aux = genes.charAt(a);
        char aux2 = genes.charAt(b);
        String s = "";
        for (int i=0 ; i<genes.length() ; i++) {
          if(i == a){
            s += aux2;
          }else if(i == b){
            s += aux;
          }else{
            s += genes.charAt(i);
          }
        }
        genes = s;
        setAptitud();
      }
  }

  public Genotipo clonar(){
    Genotipo g = new Genotipo(genes);
    return g;
  }

  private void setAptitud(){
    int j=0;
    for (int i=0 ; i<genes.length() ; i++) {
      j=i+1;
      if(j<genes.length()){
        this.aptitud += Ciudades.distanciasXY(genes.charAt(i), genes.charAt(j));
      }
    }
  }

  public String getGenes(){
    return genes;
  }

  public long getAptitud(){
    return aptitud;
  }

  public String toString(){
    String aux = genes + "\t" + aptitud;
    return aux;
  }
}
