package geneticosimple;

/**
 *
 * @author alejandro
 */
public class Main {
  public static void main(String[] args) {
    GeneticoSimple gs = new GeneticoSimple();
    gs.iniciar();
    for (int i=0 ; i<10000 ; i++) {
      gs.seleccion();
      gs.generaHijos();
      gs.ordenaPadres();
      gs.maxGeneracion();
      gs.generaMutantes();
      gs.filtraAptitud();
      gs.maxGeneracion();
      /*System.out.println(gs.printPadres());
      System.out.print("\n\n");
      System.out.println(gs.printHijos());
      System.out.print("\n\n");
      gs.generaMutantes();
      System.out.println(gs.printHijos());
      System.out.print("\n\n");

      System.out.println(gs.printPadres());
      gs.maxGeneracion();
      System.out.print("\n\n");
      */
    }
    System.out.print(gs.printMejores());
  }
}

