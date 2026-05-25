import matplotlib.pyplot as plt
import numpy as np

n_vals = [1000, 5000, 10000, 50000, 100000, 500000, 1000000]
t_vals = [0.001, 0.017, 0.05, 1.231, 8.214, 197.093, 788.372]

# Подбираем константу c для O(n^2): t = c * n^2
c_list = [t / (n ** 2) for n, t in zip(n_vals, t_vals)]
c = np.mean(c_list)

# Прогноз для N = 2 000 000
n_forecast = 2_000_000
t_forecast = c * n_forecast ** 2

print(f"Константа c = {c:.3e}")
print(f"Прогноз для N=2,000,000: {t_forecast:.1f} сек")

n_curve = np.geomspace(min(n_vals), n_forecast, 300)
t_curve = c * n_curve ** 2

fig, ax = plt.subplots(figsize=(12, 7))

ax.plot(n_curve, t_curve, color='tomato', linewidth=2,
        linestyle='--', alpha=0.7, label=r'Теория: $O(n^2)$')

ax.plot(n_vals, t_vals, color='steelblue', linewidth=2,
        marker='o', markersize=8, label='Реальные замеры')

# Прогнозная точка
ax.plot(n_forecast, t_forecast, marker='*', markersize=14,
        color='crimson', zorder=5,
        label=f'Прогноз N=2 000 000: {t_forecast:.0f} сек')

for n, t in zip(n_vals, t_vals):
    ax.annotate(f'{t}s', xy=(n, t),
                xytext=(0, 10), textcoords='offset points',
                ha='center', fontsize=8, color='steelblue', fontweight='bold')

ax.annotate(f'{t_forecast:.0f}s', xy=(n_forecast, t_forecast),
            xytext=(-50, 10), textcoords='offset points',
            ha='center', fontsize=9, color='crimson', fontweight='bold')

ax.set_xscale('log')
ax.set_yscale('log')
ax.grid(True, which='both', linestyle=':', alpha=0.6)

ax.set_title('Анализ сложности алгоритма Иосифа', fontsize=14, pad=15)
ax.set_xlabel('Размер входных данных N', fontsize=12)
ax.set_ylabel('Время выполнения', fontsize=12)

tick_positions = n_vals + [n_forecast]
ax.set_xticks(tick_positions)
ax.set_xticklabels([f'{v:,}'.replace(',', ' ') for v in tick_positions], rotation=45, ha='right')

ax.legend(fontsize=11)
fig.tight_layout()
fig.savefig('./prognoz.png', dpi=150)
print("График сохранён: prognoz.png")
