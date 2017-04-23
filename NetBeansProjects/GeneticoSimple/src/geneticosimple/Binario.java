package geneticosimple;

/**
 *
 * @author alejandro
 */
public final class Binario {
    
    public static String binarioAleaotrioDe(int elementos){
        String str = "";
        for(int i = 0; i<elementos; i++){
            str += (int)(Math.random()*2);
        }
        return str;
    }
}
