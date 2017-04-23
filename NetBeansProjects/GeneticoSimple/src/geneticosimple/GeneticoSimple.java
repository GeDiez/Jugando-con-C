
package geneticosimple;

import java.util.ArrayList;

/**
 *
 * @author alejandro
 */

public class GeneticoSimple{
  private final int poblacion = 3000;
  private final int lim = 16;
  private Organismo padre[];
  private Organismo hijo[];
  private Organismo xy[][];
  private ArrayList<Organismo> mejores;

  public GeneticoSimple(){
    mejores = new ArrayList<Organismo>();
    padre = new Organismo[poblacion];
    hijo = new Organismo[poblacion];
    xy = new Organismo [poblacion/2][2];
  }

  public void iniciar(){
    for (int i=0 ; i<poblacion ; i++) {
      String aux = "";
      int tamBinario = (int) ((Math.random() * lim) + 5);
      for (int j=0 ; j<tamBinario ; j++) {
        aux += (int)(Math.random() * 2);
      }
      padre[i] = new Organismo(aux);
    }
  }

  public void seleccion(){
    ArrayList<Integer> index = new ArrayList<Integer>();
    for(int i=0 ; i<poblacion ; i++){
      index.add(i);
    }
    for(int i=0 ; i<poblacion/2 ; i++){
      int id = (int) (Math.random() * (index.size()));
      xy[i][0] = padre[index.get(id)].clone();
      index.remove(id);
      id = (int) (Math.random() * (index.size()));
      xy[i][1] = padre[index.get(id)].clone();
      index.remove(id);
    }
  }

  public void ordenaPadres(){
    int index = 0;
    for(int i=0 ; i<poblacion/2 ;i++){
      padre[index++] = xy[i][0].clone();
      padre[index++] = xy[i][1].clone();
    }
  }

  public void generaHijos(){
    int index = 0;
    for(int i=0 ; i<poblacion/2 ; i++){
      String gen = "";
      gen = xy[i][0].getGenes().substring(0,2) + xy[i][1].getGenes().substring(2,xy[i][1].getGenes().length());
      hijo[index++] = new Organismo(gen);
      gen = xy[i][1].getGenes().substring(0,2) + xy[i][0].getGenes().substring(2,xy[i][0].getGenes().length());
      hijo[index++] = new Organismo(gen);
    }
  }

  public void generaMutantes(){
    for (int i=0 ; i<poblacion ; i++) {
      int muta = (int) (Math.random() * 2);
      if(muta == 1){
        hijo[i].mutar(true);
      }
    }
  }

  public void filtraAptitud(){
    for (int i=0 ; i<poblacion ; i++) {
      if(hijo[i].getAptitud() > padre[i].getAptitud()){
        padre[i] = hijo[i].clone();
      }
    }
  }

  public void maxGeneracion(){
    Organismo aux = new Organismo("00000");
    for (int i=0 ; i<poblacion ; i++) {
      if(padre[i].getAptitud() > aux.getAptitud()){
        aux = padre[i].clone();
      }
    }
    mejores.add(aux);
  }

  public String printPadres(){
    String aux = "";
    for (int i=0 ; i<poblacion ; i++) {
      aux += i + "\t" + padre[i] + "\n";
    }
    return aux;
  }

  public String printHijos(){
    String aux = "";
    for (int i=0 ; i<poblacion ; i++) {
      aux += i + "\t" + hijo[i] + "\n";
    }
    return aux;
  }

  public String printXY(){
    String aux = "";
    for (int i=0 ; i<poblacion/2 ; i++) {
      aux += i + "\t" + xy[i][0] + "\t\t" + xy[i][1] + "\n";
    }
    return aux;
  }

  public String printMejores(){
    String aux = "";
    for(Organismo o : mejores){
      aux += o + "\n";
    }
    return aux;
  }
}
