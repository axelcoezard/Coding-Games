import java.util.*;

    /****************************************************************************************
    * Vec2 CLASSE
    /***************************************************************************************/
class Vec2
{
    int x;
    int y;

    Vec2(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public Entity getNearestEntity(List<Entity> entities)
    {
        // Je prend le premier par default
        if (entities.isEmpty())
            return null;
        Entity e = entities.get(0);
        double dist = e.getDistance(x, y);
        // Je cherche le plus proche
        for (int i = 1; i < entities.size(); i++)
        {
            Entity tmp = entities.get(i);
            double tmp_d = tmp.getDistance(x, y);
            if (tmp_d < dist)
            {
                e = tmp;
                dist = tmp_d;
            }
        }
        return e;
    }
}

    /****************************************************************************************
    * BASE CLASSE
    /***************************************************************************************/
class Zone
{
    int type;
    int x;
    int y;

    Zone(int x, int y, int type)
    {
        this.type = type;
        this.x = x;
        this.y = y;
    }

    public boolean isEntityToward(Entity e)
    {
        return isEntityToward(e, 5000);
    }

    public boolean isEntityToward(Entity e, int radius)
    {
        if (e.vx == 0)
            return true;
        double A = e.vy / e.vx;
        double xf = e.x + e.vx;
        double yf = e.y + e.vy;
        double truc = yf - A * xf - this.y;

        double alpha = A * A + 1;
        double beta = 2 * A * truc - 2 * this.x;
        double gamma = this.x * this.x + truc * truc - radius * radius;
        return (beta * beta - 4 * alpha * gamma) >= 0 && e.threatFor == this.type;
    }

    private List<Entity> getEntitiesToward(List<Entity> entities, int radius)
    {
        List<Entity> towards = new ArrayList<>();
        for (int i = 0; i < entities.size(); i++)
        {
            Entity tmp = entities.get(i);
            if (isEntityToward(tmp, radius))
                towards.add(tmp);
        }
        return towards;
    }

    public Entity getNearestEntityToward(List<Entity> entities)
    {
        return getNearestEntityToward(entities, 5000);
    }

    public Entity getNearestEntityToward(List<Entity> entities, int radius)
    {
        // Je recupere tous les monstres en direction de la base
        List<Entity> towards = getEntitiesToward(entities, radius);
        // Je prend le premier par default
        if (towards.isEmpty())
            return null;
        Entity e = towards.get(0);
        double dist = e.getDistance(this);
        // Je cherche le plus proche
        for (int i = 1; i < towards.size(); i++)
        {
            Entity tmp = towards.get(i);
            double tmp_d = tmp.getDistance(this);
            if (tmp_d < dist)
            {
                e = tmp;
                dist = tmp_d;
            }
        }
        return e;
    }
}

    /****************************************************************************************
    * ENTITY CLASSE
    /***************************************************************************************/
class Entity
{
    int id;
    int type;
    int x, y;
    int shieldLife;
    int isControlled;
    int health;
    int vx, vy;
    int nearZone;
    int threatFor;

    Entity(int id, int type, int x, int y, int shieldLife, int isControlled, int health, int vx, int vy, int nearZone, int threatFor) {
        this.id = id;
        this.type = type;
        this.x = x;
        this.y = y;
        this.shieldLife = shieldLife;
        this.isControlled = isControlled;
        this.health = health;
        this.vx = vx;
        this.vy = vy;
        this.nearZone = nearZone;
        this.threatFor = threatFor;
    }

    private double getDistance(int xa, int ya, int xb, int yb)
    {
        double xx = xb - xa;
        double yy = yb - ya;
        return Math.sqrt(xx * xx + yy * yy);
    }

    public double getDistance(int x, int y)
    {
        return getDistance(this.x, this.y, x, y);
    }

    public double getDistance(Zone zone)
    {
        return getDistance(this.x, this.y, zone.x, zone.y);
    }

    public double getDistance(Entity b)
    {
        return getDistance(this.x, this.y, b.x, b.y);
    }
}

    /****************************************************************************************
    * HERO CLASSE
    /***************************************************************************************/
class Hero extends Entity
{
    Hero(int id, int type, int x, int y, int shieldLife, int isControlled, int health, int vx, int vy, int nearZone, int threatFor)
    {
        super(id, type, x, y, shieldLife, isControlled, health, vx, vy, nearZone, threatFor);
    }

    public void move(int x, int y)
    {
        System.out.println(String.format("MOVE %d %d defend", x , y));
    }

    public void move(Vec2 pos)
    {
        this.move(pos.x, pos.y);
    }

    public void attack(Entity e)
    {
        this.move(e.x, e.y);
    }

    public void control(Entity e, int x, int y)
    {
        System.out.println(String.format("SPELL CONTROL %d %d %d control", e.id, x, y));
    }

    public void control(Entity e, Zone zone)
    {
       this.control(e, zone.x, zone.y);
    }

    public void shield(Entity e)
    {
        System.out.println(String.format("SPELL SHIELD %d shield", e.id));
    }

    public void wind(int vx, int vy)
    {
        System.out.println(String.format("SPELL WIND %d %d wind", vx, vy));
    }

    public void wind(Entity e)
    {
        this.wind(e.x - e.vx, e.y - e.vy);
    }

    public void wind(Zone zone)
    {
        this.wind(zone.x, zone.y);
    }

    public void await()
    {
        System.out.println("WAIT");
    }

    public Entity getNearestEntity(List<Entity> entities)
    {
        return (new Vec2(x, y)).getNearestEntity(entities);
    }

    public Vec2 getStartPosition(Zone base)
    {
        Vec2 pos = new Vec2(base.x, base.y);

        int id = this.id % 3;
        int radius = 7000;
        double angle = (id + 1) * Math.PI / 8;
        int sign = base.x != 0 && base.y != 0 ? -1 : 1;
        pos.x += sign * (int) (Math.cos(angle) * radius);
        pos.y += sign * (int) (Math.sin(angle) * radius);
        return pos;
    }
}

class Player
{
	/****************************************************************************************
	 * CONSTANTES
	/***************************************************************************************/
    static final int TYPE_MONSTER = 0;
    static final int TYPE_MY_HERO = 1;
    static final int TYPE_OP_HERO = 2;

    static final int TYPE_MY_BASE = 1;
    static final int TYPE_OP_BASE = 2;

    /****************************************************************************************
	 * VARIABLES
	/***************************************************************************************/
    public Zone base, ennemyZone;

    public int heroesPerPlayer;

    public int health;
    public int mana;
    public int oppHealth;
    public int oppMana;
    public int entityCount;

    public boolean wind;
    public boolean control;

    public List<Entity> monsters = new ArrayList<>(entityCount);
    public List<Entity> ennemies = new ArrayList<>(entityCount);
    public List<Hero> heroes = new ArrayList<>(entityCount);
    private List<Entity> focus = new ArrayList<>();

    /****************************************************************************************
	 * MAIN LOOP
	/***************************************************************************************/
    public void loop()
    {
        Scanner in = new Scanner(System.in);

		base = new Zone(in.nextInt(), in.nextInt(), TYPE_MY_BASE);
        ennemyZone = (base.x == 0 && base.y == 0)
            ? new Zone(17630, 9000, TYPE_OP_BASE)
            : new Zone(0, 0, TYPE_OP_BASE);
        heroesPerPlayer = in.nextInt();

        while (true)
        {
            this.parse(in);
            this.farm_strategy();
            this.cleanup();
        }
    }

    /****************************************************************************************
	 * PARSING
	/***************************************************************************************/
    private void parse(Scanner in)
    {
        health = in.nextInt();
        mana = in.nextInt();
        oppHealth = in.nextInt();
        oppMana = in.nextInt();
        entityCount = in.nextInt();

        for (int i = 0; i < entityCount; i++)
        {
            int id = in.nextInt();              // Unique identifier
            int type = in.nextInt();            // 0=monster, 1=your hero, 2=opponent hero
            int x = in.nextInt();               // Position of this entity
            int y = in.nextInt();
            int shieldLife = in.nextInt();      // Ignore for this league; Count down until shield spell fades
            int isControlled = in.nextInt();    // Ignore for this league; Equals 1 when this entity is under a control spell
            int health = in.nextInt();          // Remaining health of this monster
            int vx = in.nextInt();              // Trajectory of this monster
            int vy = in.nextInt();
            int nearZone = in.nextInt();        // 0=monster with no target yet, 1=monster targeting a base
            int threatFor = in.nextInt();       // Given this monster's trajectory, is it a threat to 1=your base, 2=your opponent's base, 0=neither

            Hero entity = new Hero(
                id, type, x, y, shieldLife, isControlled, health, vx, vy, nearZone, threatFor
            );

            switch (type)
            {
                case TYPE_MONSTER:
                    monsters.add((Entity) entity);
                    break;
                case TYPE_MY_HERO:
                    heroes.add(entity);
                    break;
                case TYPE_OP_HERO:
                    ennemies.add((Entity) entity);
                    break;
            }
        }
    }

    /****************************************************************************************
	 * STRATEGY FARM
	/***************************************************************************************/
    private Entity farm_strategy_focus(Hero hero)
    {
        Entity targetA = null;
        Entity targetB = null;

        if (monsters.isEmpty())
            return null;

        targetA = monsters.get(0);
        Vec2 pos = hero.getStartPosition(base);
        double dist = targetA.getDistance(pos.x, pos.y);
        for (int i = 1; i < monsters.size(); i++)
        {
            Entity tmp = monsters.get(i);
            double tmp_d = tmp.getDistance(pos.x, pos.y);
            if (focus.contains(tmp))
                continue;
            if (tmp_d < dist)
            {
                targetA = tmp;
                dist = tmp_d;
            }
        }

        targetB = base.getNearestEntityToward(monsters);

        if (focus.contains(targetA))
            return targetB;
        if (targetB == null)
            return targetA;

        if (targetB.getDistance(base) < 6000)
            return targetB;

        return targetA.getDistance(hero) <= targetB.getDistance(hero)
            ? targetA
            : targetB;
    }

    private void farm_strategy()
    {

        wind = false;
        control = false;
        for (int i = 0; i < heroesPerPlayer; i++)
        {
            Hero hero = heroes.get(i);
            double myDistance = hero.getDistance(base);

            Entity target = farm_strategy_focus(hero);

            if (target != null)
            {
                focus.add(target);

                double itsDistance = target.getDistance(base);
                if (!wind
                    && myDistance < itsDistance
                    && target.getDistance(hero) < 1280
                    && target.getDistance(base) < 6000)
                {
                    hero.wind(target);
                    wind = true;
                }
                else hero.attack(target);
            }
            else hero.move(hero.getStartPosition(base));

        }
        wind = false;
        control = false;
    }

    /****************************************************************************************
	 * MAIN CLEAN UP
	/***************************************************************************************/
    private void cleanup()
    {
        monsters.clear();
        heroes.clear();
        ennemies.clear();
        focus.clear();
    }

    /****************************************************************************************
	 * MAIN
	/***************************************************************************************/
    public static void main(String args[])
	{
       Player player = new Player();
       player.loop();
    }
}
