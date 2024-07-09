import java.util.List;

public class SubstringFilter implements Filter{

    @Override
    public boolean select(Produto product, List<String> parameter){
        return product.getDescricao().toLowerCase().contains(parameter.get(0).toLowerCase());
    }
}