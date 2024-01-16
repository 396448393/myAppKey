import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

import AutoImport from 'unplugin-auto-import/vite'
import Components from 'unplugin-vue-components/vite'
import { ElementPlusResolver } from 'unplugin-vue-components/resolvers'

// https://vitejs.dev/config/
export default defineConfig({
build: {
    outDir: '../esp32App/www', //指定输出路径
    assetsPublicPath: './',
  },
  plugins: [
    vue(),
	 AutoImport({
	      resolvers: [ElementPlusResolver()],
	    }),
	    Components({
	      resolvers: [ElementPlusResolver()],
	    }),
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  },
    //静态资源服务的文件夹
    base: './',
    server: {
        proxy: {
            '/api': {
                target: 'http://0.0.0.0:80',	//实际请求地址
                changeOrigin: true,
                rewrite: (path) => path.replace(/^\/api/, '')
            },
        }
    },
})
