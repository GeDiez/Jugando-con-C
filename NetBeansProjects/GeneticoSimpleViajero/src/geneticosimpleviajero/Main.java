package geneticosimpleviajero;

/**
 *
 * @author alejandro
 */
public class Main{
  public static void main(String[] args) {
    GeneticoSimple gs = new GeneticoSimple();
    gs.iniciar();
    for (int i=0 ; i<10000 ; i++) {
      gs.seleccion();
      gs.ordenaPadres();;
      gs.generarHijos();
      gs.generaMutantes();
      gs.filtraAptitud();
      gs.mejorGeneracion();
    }
    System.out.println(gs.printMejores());
  }
}
