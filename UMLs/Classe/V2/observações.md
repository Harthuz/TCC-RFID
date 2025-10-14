**Observações:**
- Todas as "classes" são JS modules/funções, representadas como classes para fins de UML.
- Não há interfaces formais, mas os métodos públicos estão destacados.
- Não há herança explícita (extends), mas as dependências e associações estão ilustradas.
- Os relacionamentos principais entre MVC (Controllers → Models → DB, Controllers → Services, Rotas → Controllers, Server → tudo) estão indicados por setas.
- O fluxo típico é: **Rotas → Middleware → Controller → Model → DB** e **Controller → Service**.
- Os métodos privados em JS são apenas por convenção (prefixados com "-").
- Não há visualização explicitamente implementada (Views) no backend; a resposta HTTP serve como "View" em uma API REST.