package geneticosimple;

/**
 *
 * @author alejandro
 */
public class Organismo implements Cloneable{

  private String genes;
  private long aptitud;

  public Organismo(String genes){
    this.genes = genes;
    setAptitud(genes);
  }

  private void setAptitud(String genes){
    this.aptitud = (long)Math.pow(Long.parseLong(genes, 2), 2);
  }

  public void mutar(boolean mutar){
    if(mutar){
      int nBit = (int)(Math.random() * genes.length());
      if(genes.charAt(nBit) == '1'){
        genes = genes.substring(0,nBit++) + '0' + genes.substring(nBit++,genes.length());
      }else{
        genes = genes.substring(0,nBit++) + '1' + genes.substring(nBit++,genes.length());
      }
      setAptitud(genes);

    }
  }

  public String getGenes(){
    return genes;
  }

  public long getAptitud(){
    return aptitud;
  }

  public Organismo clone(){
    Organismo clon = new Organismo(genes);
    return clon;
  }

  public String toString(){
    String aux = "";
    aux = genes + "\t" + aptitud;
    return aux;
  }
}
