import java.util.List;

public class AllProductsFilter implements Filter{

    @Override
    public boolean select(Produto products, List<String> parameter){
        return true;
    }
}