
package geneticosimpleviajero;

import java.util.ArrayList;

/**
 *
 * @author alejandro
 */

public class GeneticoSimple {
  private final int poblacion = 100;
  private final int genes = 11;
  private final char cinicial = 'a';
  private Genotipo padre[];
  private Genotipo hijo[];
  private Genotipo xy[][];
  private ArrayList<Genotipo> mejores;

  public GeneticoSimple(){
    mejores = new ArrayList<Genotipo>();
    padre = new Genotipo[poblacion];
    hijo = new Genotipo[poblacion];
    xy = new Genotipo[poblacion/2][2];
  }

  public void iniciar(){
    for(int i=0 ; i<poblacion ; i++){
      String aux;
      aux = "" + cinicial;
      ArrayList<Integer> index = new ArrayList<Integer>();
      for(int j=0 ; j<genes-1 ; j++){
        if(Ciudades.getCiudad(j) != cinicial){
          index.add(j);
        }
      }
      for (int j=0 ; j<genes-2 ; j++) {
          int id = (int)(Math.random() * (index.size()));
          aux += Ciudades.getCiudad(index.get(id));
          index.remove(id);
      }
      aux += cinicial;
      padre[i] = new Genotipo(aux);
    }
  }

  public void seleccion(){
    ArrayList<Genotipo> index = new ArrayList<Genotipo>();
    for(int i=0 ; i<poblacion ; i++){
      index.add(padre[i]);
    }
    for (int i=0 ; i<poblacion/2 ; i++) {
      for(int j=0 ; j<2 ; j++){
        int id = (int)(Math.random() * (index.size()));
        xy[i][j] = index.get(id);
        index.remove(id);
      }
    }
  }

  public void ordenaPadres(){
    int index = 0;
    for(int i=0 ; i<poblacion/2 ;i++){
      for(int j=0 ; j<2 ; j++){
        padre[index++] = xy[i][j];
      }
    }
  }

  public void generarHijos(){
    int index = 0;
    for (int i=0 ; i<poblacion/2 ; i++) {
      String gen = "";
      int pivote = (int)(Math.random() * (genes - 3) + 2);
      gen = xy[i][0].getGenes().substring(0,pivote);
      for (int j=0 ; j<genes ; j++) {
        if(gen.indexOf(xy[i][1].getGenes().charAt(j)) == -1){
          gen += xy[i][1].getGenes().charAt(j);
        }
      }
      gen += cinicial;
      hijo[index++] = new Genotipo(gen);
      gen = xy[i][1].getGenes().substring(0, pivote);
      for (int j=0 ; j<genes ; j++) {
        if(gen.indexOf(xy[i][0].getGenes().charAt(j)) == -1){
          gen += xy[i][0].getGenes().charAt(j);
        }
      }
      gen += cinicial;
      hijo[index++] = new Genotipo(gen);
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
      if(hijo[i].getAptitud() < padre[i].getAptitud()){
        padre[i] = hijo[i];
      }
    }
  }

  public void mejorGeneracion(){
    Genotipo aux = new Genotipo("ajcibhdfgea");
    for (int i=0 ; i<poblacion ; i++) {
      if(padre[i].getAptitud() < aux.getAptitud()){
        aux = padre[i];
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
    int i=1;
    for(Genotipo o : mejores){
      aux += i + "\t orden : " + o + "\n";
      i++;
    }
    return aux;
  }
}