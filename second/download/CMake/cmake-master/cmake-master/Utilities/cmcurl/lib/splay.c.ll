; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.timeval = type { i64, i64 }
%struct.Curl_tree = type { %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.timeval, i8* }

@Curl_splayinsert.KEY_NOTUSED = internal constant %struct.timeval { i64 -1, i64 -1 }, align 8
@Curl_splaygetbest.tv_zero = internal global %struct.timeval zeroinitializer, align 8
@Curl_splayremovebyaddr.KEY_NOTUSED = internal constant %struct.timeval { i64 -1, i64 -1 }, align 8

; Function Attrs: nounwind uwtable
define %struct.Curl_tree* @Curl_splay(i64 %i.coerce0, i64 %i.coerce1, %struct.Curl_tree* %t) #0 !dbg !6 {
entry:
  %retval = alloca %struct.Curl_tree*, align 8
  %i = alloca %struct.timeval, align 8
  %t.addr = alloca %struct.Curl_tree*, align 8
  %N = alloca %struct.Curl_tree, align 8
  %l = alloca %struct.Curl_tree*, align 8
  %r = alloca %struct.Curl_tree*, align 8
  %y = alloca %struct.Curl_tree*, align 8
  %comp = alloca i64, align 8
  %0 = bitcast %struct.timeval* %i to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %i.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %i.coerce1, i64* %2, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %i, metadata !47, metadata !48), !dbg !49
  store %struct.Curl_tree* %t, %struct.Curl_tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %t.addr, metadata !50, metadata !48), !dbg !51
  call void @llvm.dbg.declare(metadata %struct.Curl_tree* %N, metadata !52, metadata !48), !dbg !53
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %l, metadata !54, metadata !48), !dbg !55
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %r, metadata !56, metadata !48), !dbg !57
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %y, metadata !58, metadata !48), !dbg !59
  call void @llvm.dbg.declare(metadata i64* %comp, metadata !60, metadata !48), !dbg !61
  %3 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !62
  %cmp = icmp eq %struct.Curl_tree* %3, null, !dbg !64
  br i1 %cmp, label %if.then, label %if.end, !dbg !65

if.then:                                          ; preds = %entry
  %4 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !66
  store %struct.Curl_tree* %4, %struct.Curl_tree** %retval, align 8, !dbg !67
  br label %return, !dbg !67

if.end:                                           ; preds = %entry
  %larger = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %N, i32 0, i32 1, !dbg !68
  store %struct.Curl_tree* null, %struct.Curl_tree** %larger, align 8, !dbg !69
  %smaller = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %N, i32 0, i32 0, !dbg !70
  store %struct.Curl_tree* null, %struct.Curl_tree** %smaller, align 8, !dbg !71
  store %struct.Curl_tree* %N, %struct.Curl_tree** %r, align 8, !dbg !72
  store %struct.Curl_tree* %N, %struct.Curl_tree** %l, align 8, !dbg !73
  br label %for.cond, !dbg !74

for.cond:                                         ; preds = %if.end145, %if.end
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !75
  %5 = load i64, i64* %tv_sec, align 8, !dbg !75
  %6 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !75
  %key = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %6, i32 0, i32 4, !dbg !75
  %tv_sec1 = getelementptr inbounds %struct.timeval, %struct.timeval* %key, i32 0, i32 0, !dbg !75
  %7 = load i64, i64* %tv_sec1, align 8, !dbg !75
  %cmp2 = icmp slt i64 %5, %7, !dbg !75
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !75

cond.true:                                        ; preds = %for.cond
  br label %cond.end21, !dbg !79

cond.false:                                       ; preds = %for.cond
  %tv_sec3 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !81
  %8 = load i64, i64* %tv_sec3, align 8, !dbg !81
  %9 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !81
  %key4 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %9, i32 0, i32 4, !dbg !81
  %tv_sec5 = getelementptr inbounds %struct.timeval, %struct.timeval* %key4, i32 0, i32 0, !dbg !81
  %10 = load i64, i64* %tv_sec5, align 8, !dbg !81
  %cmp6 = icmp sgt i64 %8, %10, !dbg !81
  br i1 %cmp6, label %cond.true7, label %cond.false8, !dbg !81

cond.true7:                                       ; preds = %cond.false
  br label %cond.end19, !dbg !83

cond.false8:                                      ; preds = %cond.false
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !85
  %11 = load i64, i64* %tv_usec, align 8, !dbg !85
  %12 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !85
  %key9 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %12, i32 0, i32 4, !dbg !85
  %tv_usec10 = getelementptr inbounds %struct.timeval, %struct.timeval* %key9, i32 0, i32 1, !dbg !85
  %13 = load i64, i64* %tv_usec10, align 8, !dbg !85
  %cmp11 = icmp slt i64 %11, %13, !dbg !85
  br i1 %cmp11, label %cond.true12, label %cond.false13, !dbg !85

cond.true12:                                      ; preds = %cond.false8
  br label %cond.end, !dbg !87

cond.false13:                                     ; preds = %cond.false8
  %tv_usec14 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !89
  %14 = load i64, i64* %tv_usec14, align 8, !dbg !89
  %15 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !89
  %key15 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %15, i32 0, i32 4, !dbg !89
  %tv_usec16 = getelementptr inbounds %struct.timeval, %struct.timeval* %key15, i32 0, i32 1, !dbg !89
  %16 = load i64, i64* %tv_usec16, align 8, !dbg !89
  %cmp17 = icmp sgt i64 %14, %16, !dbg !89
  %cond = select i1 %cmp17, i32 1, i32 0, !dbg !89
  br label %cond.end, !dbg !89

cond.end:                                         ; preds = %cond.false13, %cond.true12
  %cond18 = phi i32 [ -1, %cond.true12 ], [ %cond, %cond.false13 ], !dbg !91
  br label %cond.end19, !dbg !91

cond.end19:                                       ; preds = %cond.end, %cond.true7
  %cond20 = phi i32 [ 1, %cond.true7 ], [ %cond18, %cond.end ], !dbg !93
  br label %cond.end21, !dbg !93

cond.end21:                                       ; preds = %cond.end19, %cond.true
  %cond22 = phi i32 [ -1, %cond.true ], [ %cond20, %cond.end19 ], !dbg !95
  %conv = sext i32 %cond22 to i64, !dbg !95
  store i64 %conv, i64* %comp, align 8, !dbg !97
  %17 = load i64, i64* %comp, align 8, !dbg !98
  %cmp23 = icmp slt i64 %17, 0, !dbg !100
  br i1 %cmp23, label %if.then25, label %if.else, !dbg !101

if.then25:                                        ; preds = %cond.end21
  %18 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !102
  %smaller26 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %18, i32 0, i32 0, !dbg !105
  %19 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller26, align 8, !dbg !105
  %cmp27 = icmp eq %struct.Curl_tree* %19, null, !dbg !106
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !107

if.then29:                                        ; preds = %if.then25
  br label %for.end, !dbg !108

if.end30:                                         ; preds = %if.then25
  %tv_sec31 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !109
  %20 = load i64, i64* %tv_sec31, align 8, !dbg !109
  %21 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !109
  %smaller32 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %21, i32 0, i32 0, !dbg !109
  %22 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller32, align 8, !dbg !109
  %key33 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %22, i32 0, i32 4, !dbg !109
  %tv_sec34 = getelementptr inbounds %struct.timeval, %struct.timeval* %key33, i32 0, i32 0, !dbg !109
  %23 = load i64, i64* %tv_sec34, align 8, !dbg !109
  %cmp35 = icmp slt i64 %20, %23, !dbg !109
  br i1 %cmp35, label %cond.true37, label %cond.false38, !dbg !109

cond.true37:                                      ; preds = %if.end30
  br label %cond.end66, !dbg !111

cond.false38:                                     ; preds = %if.end30
  %tv_sec39 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !113
  %24 = load i64, i64* %tv_sec39, align 8, !dbg !113
  %25 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !113
  %smaller40 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %25, i32 0, i32 0, !dbg !113
  %26 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller40, align 8, !dbg !113
  %key41 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %26, i32 0, i32 4, !dbg !113
  %tv_sec42 = getelementptr inbounds %struct.timeval, %struct.timeval* %key41, i32 0, i32 0, !dbg !113
  %27 = load i64, i64* %tv_sec42, align 8, !dbg !113
  %cmp43 = icmp sgt i64 %24, %27, !dbg !113
  br i1 %cmp43, label %cond.true45, label %cond.false46, !dbg !113

cond.true45:                                      ; preds = %cond.false38
  br label %cond.end64, !dbg !115

cond.false46:                                     ; preds = %cond.false38
  %tv_usec47 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !117
  %28 = load i64, i64* %tv_usec47, align 8, !dbg !117
  %29 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !117
  %smaller48 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %29, i32 0, i32 0, !dbg !117
  %30 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller48, align 8, !dbg !117
  %key49 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %30, i32 0, i32 4, !dbg !117
  %tv_usec50 = getelementptr inbounds %struct.timeval, %struct.timeval* %key49, i32 0, i32 1, !dbg !117
  %31 = load i64, i64* %tv_usec50, align 8, !dbg !117
  %cmp51 = icmp slt i64 %28, %31, !dbg !117
  br i1 %cmp51, label %cond.true53, label %cond.false54, !dbg !117

cond.true53:                                      ; preds = %cond.false46
  br label %cond.end62, !dbg !119

cond.false54:                                     ; preds = %cond.false46
  %tv_usec55 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !121
  %32 = load i64, i64* %tv_usec55, align 8, !dbg !121
  %33 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !121
  %smaller56 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %33, i32 0, i32 0, !dbg !121
  %34 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller56, align 8, !dbg !121
  %key57 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %34, i32 0, i32 4, !dbg !121
  %tv_usec58 = getelementptr inbounds %struct.timeval, %struct.timeval* %key57, i32 0, i32 1, !dbg !121
  %35 = load i64, i64* %tv_usec58, align 8, !dbg !121
  %cmp59 = icmp sgt i64 %32, %35, !dbg !121
  %cond61 = select i1 %cmp59, i32 1, i32 0, !dbg !121
  br label %cond.end62, !dbg !121

cond.end62:                                       ; preds = %cond.false54, %cond.true53
  %cond63 = phi i32 [ -1, %cond.true53 ], [ %cond61, %cond.false54 ], !dbg !123
  br label %cond.end64, !dbg !123

cond.end64:                                       ; preds = %cond.end62, %cond.true45
  %cond65 = phi i32 [ 1, %cond.true45 ], [ %cond63, %cond.end62 ], !dbg !125
  br label %cond.end66, !dbg !125

cond.end66:                                       ; preds = %cond.end64, %cond.true37
  %cond67 = phi i32 [ -1, %cond.true37 ], [ %cond65, %cond.end64 ], !dbg !127
  %cmp68 = icmp slt i32 %cond67, 0, !dbg !129
  br i1 %cmp68, label %if.then70, label %if.end80, !dbg !127

if.then70:                                        ; preds = %cond.end66
  %36 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !130
  %smaller71 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %36, i32 0, i32 0, !dbg !132
  %37 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller71, align 8, !dbg !132
  store %struct.Curl_tree* %37, %struct.Curl_tree** %y, align 8, !dbg !133
  %38 = load %struct.Curl_tree*, %struct.Curl_tree** %y, align 8, !dbg !134
  %larger72 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %38, i32 0, i32 1, !dbg !135
  %39 = load %struct.Curl_tree*, %struct.Curl_tree** %larger72, align 8, !dbg !135
  %40 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !136
  %smaller73 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %40, i32 0, i32 0, !dbg !137
  store %struct.Curl_tree* %39, %struct.Curl_tree** %smaller73, align 8, !dbg !138
  %41 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !139
  %42 = load %struct.Curl_tree*, %struct.Curl_tree** %y, align 8, !dbg !140
  %larger74 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %42, i32 0, i32 1, !dbg !141
  store %struct.Curl_tree* %41, %struct.Curl_tree** %larger74, align 8, !dbg !142
  %43 = load %struct.Curl_tree*, %struct.Curl_tree** %y, align 8, !dbg !143
  store %struct.Curl_tree* %43, %struct.Curl_tree** %t.addr, align 8, !dbg !144
  %44 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !145
  %smaller75 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %44, i32 0, i32 0, !dbg !147
  %45 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller75, align 8, !dbg !147
  %cmp76 = icmp eq %struct.Curl_tree* %45, null, !dbg !148
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !149

if.then78:                                        ; preds = %if.then70
  br label %for.end, !dbg !150

if.end79:                                         ; preds = %if.then70
  br label %if.end80, !dbg !151

if.end80:                                         ; preds = %if.end79, %cond.end66
  %46 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !152
  %47 = load %struct.Curl_tree*, %struct.Curl_tree** %r, align 8, !dbg !153
  %smaller81 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %47, i32 0, i32 0, !dbg !154
  store %struct.Curl_tree* %46, %struct.Curl_tree** %smaller81, align 8, !dbg !155
  %48 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !156
  store %struct.Curl_tree* %48, %struct.Curl_tree** %r, align 8, !dbg !157
  %49 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !158
  %smaller82 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %49, i32 0, i32 0, !dbg !159
  %50 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller82, align 8, !dbg !159
  store %struct.Curl_tree* %50, %struct.Curl_tree** %t.addr, align 8, !dbg !160
  br label %if.end145, !dbg !161

if.else:                                          ; preds = %cond.end21
  %51 = load i64, i64* %comp, align 8, !dbg !162
  %cmp83 = icmp sgt i64 %51, 0, !dbg !164
  br i1 %cmp83, label %if.then85, label %if.else143, !dbg !165

if.then85:                                        ; preds = %if.else
  %52 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !166
  %larger86 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %52, i32 0, i32 1, !dbg !169
  %53 = load %struct.Curl_tree*, %struct.Curl_tree** %larger86, align 8, !dbg !169
  %cmp87 = icmp eq %struct.Curl_tree* %53, null, !dbg !170
  br i1 %cmp87, label %if.then89, label %if.end90, !dbg !171

if.then89:                                        ; preds = %if.then85
  br label %for.end, !dbg !172

if.end90:                                         ; preds = %if.then85
  %tv_sec91 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !173
  %54 = load i64, i64* %tv_sec91, align 8, !dbg !173
  %55 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !173
  %larger92 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %55, i32 0, i32 1, !dbg !173
  %56 = load %struct.Curl_tree*, %struct.Curl_tree** %larger92, align 8, !dbg !173
  %key93 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %56, i32 0, i32 4, !dbg !173
  %tv_sec94 = getelementptr inbounds %struct.timeval, %struct.timeval* %key93, i32 0, i32 0, !dbg !173
  %57 = load i64, i64* %tv_sec94, align 8, !dbg !173
  %cmp95 = icmp slt i64 %54, %57, !dbg !173
  br i1 %cmp95, label %cond.true97, label %cond.false98, !dbg !173

cond.true97:                                      ; preds = %if.end90
  br label %cond.end126, !dbg !175

cond.false98:                                     ; preds = %if.end90
  %tv_sec99 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !177
  %58 = load i64, i64* %tv_sec99, align 8, !dbg !177
  %59 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !177
  %larger100 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %59, i32 0, i32 1, !dbg !177
  %60 = load %struct.Curl_tree*, %struct.Curl_tree** %larger100, align 8, !dbg !177
  %key101 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %60, i32 0, i32 4, !dbg !177
  %tv_sec102 = getelementptr inbounds %struct.timeval, %struct.timeval* %key101, i32 0, i32 0, !dbg !177
  %61 = load i64, i64* %tv_sec102, align 8, !dbg !177
  %cmp103 = icmp sgt i64 %58, %61, !dbg !177
  br i1 %cmp103, label %cond.true105, label %cond.false106, !dbg !177

cond.true105:                                     ; preds = %cond.false98
  br label %cond.end124, !dbg !179

cond.false106:                                    ; preds = %cond.false98
  %tv_usec107 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !181
  %62 = load i64, i64* %tv_usec107, align 8, !dbg !181
  %63 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !181
  %larger108 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %63, i32 0, i32 1, !dbg !181
  %64 = load %struct.Curl_tree*, %struct.Curl_tree** %larger108, align 8, !dbg !181
  %key109 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %64, i32 0, i32 4, !dbg !181
  %tv_usec110 = getelementptr inbounds %struct.timeval, %struct.timeval* %key109, i32 0, i32 1, !dbg !181
  %65 = load i64, i64* %tv_usec110, align 8, !dbg !181
  %cmp111 = icmp slt i64 %62, %65, !dbg !181
  br i1 %cmp111, label %cond.true113, label %cond.false114, !dbg !181

cond.true113:                                     ; preds = %cond.false106
  br label %cond.end122, !dbg !183

cond.false114:                                    ; preds = %cond.false106
  %tv_usec115 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !185
  %66 = load i64, i64* %tv_usec115, align 8, !dbg !185
  %67 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !185
  %larger116 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %67, i32 0, i32 1, !dbg !185
  %68 = load %struct.Curl_tree*, %struct.Curl_tree** %larger116, align 8, !dbg !185
  %key117 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %68, i32 0, i32 4, !dbg !185
  %tv_usec118 = getelementptr inbounds %struct.timeval, %struct.timeval* %key117, i32 0, i32 1, !dbg !185
  %69 = load i64, i64* %tv_usec118, align 8, !dbg !185
  %cmp119 = icmp sgt i64 %66, %69, !dbg !185
  %cond121 = select i1 %cmp119, i32 1, i32 0, !dbg !185
  br label %cond.end122, !dbg !185

cond.end122:                                      ; preds = %cond.false114, %cond.true113
  %cond123 = phi i32 [ -1, %cond.true113 ], [ %cond121, %cond.false114 ], !dbg !187
  br label %cond.end124, !dbg !187

cond.end124:                                      ; preds = %cond.end122, %cond.true105
  %cond125 = phi i32 [ 1, %cond.true105 ], [ %cond123, %cond.end122 ], !dbg !189
  br label %cond.end126, !dbg !189

cond.end126:                                      ; preds = %cond.end124, %cond.true97
  %cond127 = phi i32 [ -1, %cond.true97 ], [ %cond125, %cond.end124 ], !dbg !191
  %cmp128 = icmp sgt i32 %cond127, 0, !dbg !193
  br i1 %cmp128, label %if.then130, label %if.end140, !dbg !191

if.then130:                                       ; preds = %cond.end126
  %70 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !194
  %larger131 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %70, i32 0, i32 1, !dbg !196
  %71 = load %struct.Curl_tree*, %struct.Curl_tree** %larger131, align 8, !dbg !196
  store %struct.Curl_tree* %71, %struct.Curl_tree** %y, align 8, !dbg !197
  %72 = load %struct.Curl_tree*, %struct.Curl_tree** %y, align 8, !dbg !198
  %smaller132 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %72, i32 0, i32 0, !dbg !199
  %73 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller132, align 8, !dbg !199
  %74 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !200
  %larger133 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %74, i32 0, i32 1, !dbg !201
  store %struct.Curl_tree* %73, %struct.Curl_tree** %larger133, align 8, !dbg !202
  %75 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !203
  %76 = load %struct.Curl_tree*, %struct.Curl_tree** %y, align 8, !dbg !204
  %smaller134 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %76, i32 0, i32 0, !dbg !205
  store %struct.Curl_tree* %75, %struct.Curl_tree** %smaller134, align 8, !dbg !206
  %77 = load %struct.Curl_tree*, %struct.Curl_tree** %y, align 8, !dbg !207
  store %struct.Curl_tree* %77, %struct.Curl_tree** %t.addr, align 8, !dbg !208
  %78 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !209
  %larger135 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %78, i32 0, i32 1, !dbg !211
  %79 = load %struct.Curl_tree*, %struct.Curl_tree** %larger135, align 8, !dbg !211
  %cmp136 = icmp eq %struct.Curl_tree* %79, null, !dbg !212
  br i1 %cmp136, label %if.then138, label %if.end139, !dbg !213

if.then138:                                       ; preds = %if.then130
  br label %for.end, !dbg !214

if.end139:                                        ; preds = %if.then130
  br label %if.end140, !dbg !215

if.end140:                                        ; preds = %if.end139, %cond.end126
  %80 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !216
  %81 = load %struct.Curl_tree*, %struct.Curl_tree** %l, align 8, !dbg !217
  %larger141 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %81, i32 0, i32 1, !dbg !218
  store %struct.Curl_tree* %80, %struct.Curl_tree** %larger141, align 8, !dbg !219
  %82 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !220
  store %struct.Curl_tree* %82, %struct.Curl_tree** %l, align 8, !dbg !221
  %83 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !222
  %larger142 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %83, i32 0, i32 1, !dbg !223
  %84 = load %struct.Curl_tree*, %struct.Curl_tree** %larger142, align 8, !dbg !223
  store %struct.Curl_tree* %84, %struct.Curl_tree** %t.addr, align 8, !dbg !224
  br label %if.end144, !dbg !225

if.else143:                                       ; preds = %if.else
  br label %for.end, !dbg !226

if.end144:                                        ; preds = %if.end140
  br label %if.end145

if.end145:                                        ; preds = %if.end144, %if.end80
  br label %for.cond, !dbg !227

for.end:                                          ; preds = %if.else143, %if.then138, %if.then89, %if.then78, %if.then29
  %85 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !229
  %smaller146 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %85, i32 0, i32 0, !dbg !230
  %86 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller146, align 8, !dbg !230
  %87 = load %struct.Curl_tree*, %struct.Curl_tree** %l, align 8, !dbg !231
  %larger147 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %87, i32 0, i32 1, !dbg !232
  store %struct.Curl_tree* %86, %struct.Curl_tree** %larger147, align 8, !dbg !233
  %88 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !234
  %larger148 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %88, i32 0, i32 1, !dbg !235
  %89 = load %struct.Curl_tree*, %struct.Curl_tree** %larger148, align 8, !dbg !235
  %90 = load %struct.Curl_tree*, %struct.Curl_tree** %r, align 8, !dbg !236
  %smaller149 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %90, i32 0, i32 0, !dbg !237
  store %struct.Curl_tree* %89, %struct.Curl_tree** %smaller149, align 8, !dbg !238
  %larger150 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %N, i32 0, i32 1, !dbg !239
  %91 = load %struct.Curl_tree*, %struct.Curl_tree** %larger150, align 8, !dbg !239
  %92 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !240
  %smaller151 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %92, i32 0, i32 0, !dbg !241
  store %struct.Curl_tree* %91, %struct.Curl_tree** %smaller151, align 8, !dbg !242
  %smaller152 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %N, i32 0, i32 0, !dbg !243
  %93 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller152, align 8, !dbg !243
  %94 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !244
  %larger153 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %94, i32 0, i32 1, !dbg !245
  store %struct.Curl_tree* %93, %struct.Curl_tree** %larger153, align 8, !dbg !246
  %95 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !247
  store %struct.Curl_tree* %95, %struct.Curl_tree** %retval, align 8, !dbg !248
  br label %return, !dbg !248

return:                                           ; preds = %for.end, %if.then
  %96 = load %struct.Curl_tree*, %struct.Curl_tree** %retval, align 8, !dbg !249
  ret %struct.Curl_tree* %96, !dbg !249
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define %struct.Curl_tree* @Curl_splayinsert(i64 %i.coerce0, i64 %i.coerce1, %struct.Curl_tree* %t, %struct.Curl_tree* %node) #0 !dbg !28 {
entry:
  %retval = alloca %struct.Curl_tree*, align 8
  %i = alloca %struct.timeval, align 8
  %t.addr = alloca %struct.Curl_tree*, align 8
  %node.addr = alloca %struct.Curl_tree*, align 8
  %0 = bitcast %struct.timeval* %i to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %i.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %i.coerce1, i64* %2, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %i, metadata !250, metadata !48), !dbg !251
  store %struct.Curl_tree* %t, %struct.Curl_tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %t.addr, metadata !252, metadata !48), !dbg !253
  store %struct.Curl_tree* %node, %struct.Curl_tree** %node.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %node.addr, metadata !254, metadata !48), !dbg !255
  %3 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !256
  %cmp = icmp eq %struct.Curl_tree* %3, null, !dbg !258
  br i1 %cmp, label %if.then, label %if.end, !dbg !259

if.then:                                          ; preds = %entry
  %4 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !260
  store %struct.Curl_tree* %4, %struct.Curl_tree** %retval, align 8, !dbg !261
  br label %return, !dbg !261

if.end:                                           ; preds = %entry
  %5 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !262
  %cmp1 = icmp ne %struct.Curl_tree* %5, null, !dbg !264
  br i1 %cmp1, label %if.then2, label %if.end33, !dbg !265

if.then2:                                         ; preds = %if.end
  %6 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !266
  %7 = bitcast %struct.timeval* %i to { i64, i64 }*, !dbg !268
  %8 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %7, i32 0, i32 0, !dbg !268
  %9 = load i64, i64* %8, align 8, !dbg !268
  %10 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %7, i32 0, i32 1, !dbg !268
  %11 = load i64, i64* %10, align 8, !dbg !268
  %call = call %struct.Curl_tree* @Curl_splay(i64 %9, i64 %11, %struct.Curl_tree* %6), !dbg !268
  store %struct.Curl_tree* %call, %struct.Curl_tree** %t.addr, align 8, !dbg !269
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !270
  %12 = load i64, i64* %tv_sec, align 8, !dbg !270
  %13 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !270
  %key = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %13, i32 0, i32 4, !dbg !270
  %tv_sec3 = getelementptr inbounds %struct.timeval, %struct.timeval* %key, i32 0, i32 0, !dbg !270
  %14 = load i64, i64* %tv_sec3, align 8, !dbg !270
  %cmp4 = icmp slt i64 %12, %14, !dbg !270
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !270

cond.true:                                        ; preds = %if.then2
  br label %cond.end23, !dbg !272

cond.false:                                       ; preds = %if.then2
  %tv_sec5 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !274
  %15 = load i64, i64* %tv_sec5, align 8, !dbg !274
  %16 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !274
  %key6 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %16, i32 0, i32 4, !dbg !274
  %tv_sec7 = getelementptr inbounds %struct.timeval, %struct.timeval* %key6, i32 0, i32 0, !dbg !274
  %17 = load i64, i64* %tv_sec7, align 8, !dbg !274
  %cmp8 = icmp sgt i64 %15, %17, !dbg !274
  br i1 %cmp8, label %cond.true9, label %cond.false10, !dbg !274

cond.true9:                                       ; preds = %cond.false
  br label %cond.end21, !dbg !276

cond.false10:                                     ; preds = %cond.false
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !278
  %18 = load i64, i64* %tv_usec, align 8, !dbg !278
  %19 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !278
  %key11 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %19, i32 0, i32 4, !dbg !278
  %tv_usec12 = getelementptr inbounds %struct.timeval, %struct.timeval* %key11, i32 0, i32 1, !dbg !278
  %20 = load i64, i64* %tv_usec12, align 8, !dbg !278
  %cmp13 = icmp slt i64 %18, %20, !dbg !278
  br i1 %cmp13, label %cond.true14, label %cond.false15, !dbg !278

cond.true14:                                      ; preds = %cond.false10
  br label %cond.end, !dbg !280

cond.false15:                                     ; preds = %cond.false10
  %tv_usec16 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !282
  %21 = load i64, i64* %tv_usec16, align 8, !dbg !282
  %22 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !282
  %key17 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %22, i32 0, i32 4, !dbg !282
  %tv_usec18 = getelementptr inbounds %struct.timeval, %struct.timeval* %key17, i32 0, i32 1, !dbg !282
  %23 = load i64, i64* %tv_usec18, align 8, !dbg !282
  %cmp19 = icmp sgt i64 %21, %23, !dbg !282
  %cond = select i1 %cmp19, i32 1, i32 0, !dbg !282
  br label %cond.end, !dbg !282

cond.end:                                         ; preds = %cond.false15, %cond.true14
  %cond20 = phi i32 [ -1, %cond.true14 ], [ %cond, %cond.false15 ], !dbg !284
  br label %cond.end21, !dbg !284

cond.end21:                                       ; preds = %cond.end, %cond.true9
  %cond22 = phi i32 [ 1, %cond.true9 ], [ %cond20, %cond.end ], !dbg !286
  br label %cond.end23, !dbg !286

cond.end23:                                       ; preds = %cond.end21, %cond.true
  %cond24 = phi i32 [ -1, %cond.true ], [ %cond22, %cond.end21 ], !dbg !288
  %cmp25 = icmp eq i32 %cond24, 0, !dbg !290
  br i1 %cmp25, label %if.then26, label %if.end32, !dbg !288

if.then26:                                        ; preds = %cond.end23
  %24 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !291
  %key27 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %24, i32 0, i32 4, !dbg !293
  %25 = bitcast %struct.timeval* %key27 to i8*, !dbg !294
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %25, i8* bitcast (%struct.timeval* @Curl_splayinsert.KEY_NOTUSED to i8*), i64 16, i32 8, i1 false), !dbg !294
  %26 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !295
  %27 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !296
  %samen = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %27, i32 0, i32 2, !dbg !297
  store %struct.Curl_tree* %26, %struct.Curl_tree** %samen, align 8, !dbg !298
  %28 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !299
  %samep = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %28, i32 0, i32 3, !dbg !300
  %29 = load %struct.Curl_tree*, %struct.Curl_tree** %samep, align 8, !dbg !300
  %30 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !301
  %samep28 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %30, i32 0, i32 3, !dbg !302
  store %struct.Curl_tree* %29, %struct.Curl_tree** %samep28, align 8, !dbg !303
  %31 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !304
  %32 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !305
  %samep29 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %32, i32 0, i32 3, !dbg !306
  %33 = load %struct.Curl_tree*, %struct.Curl_tree** %samep29, align 8, !dbg !306
  %samen30 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %33, i32 0, i32 2, !dbg !307
  store %struct.Curl_tree* %31, %struct.Curl_tree** %samen30, align 8, !dbg !308
  %34 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !309
  %35 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !310
  %samep31 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %35, i32 0, i32 3, !dbg !311
  store %struct.Curl_tree* %34, %struct.Curl_tree** %samep31, align 8, !dbg !312
  %36 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !313
  store %struct.Curl_tree* %36, %struct.Curl_tree** %retval, align 8, !dbg !314
  br label %return, !dbg !314

if.end32:                                         ; preds = %cond.end23
  br label %if.end33, !dbg !315

if.end33:                                         ; preds = %if.end32, %if.end
  %37 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !316
  %cmp34 = icmp eq %struct.Curl_tree* %37, null, !dbg !318
  br i1 %cmp34, label %if.then35, label %if.else, !dbg !319

if.then35:                                        ; preds = %if.end33
  %38 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !320
  %larger = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %38, i32 0, i32 1, !dbg !322
  store %struct.Curl_tree* null, %struct.Curl_tree** %larger, align 8, !dbg !323
  %39 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !324
  %smaller = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %39, i32 0, i32 0, !dbg !325
  store %struct.Curl_tree* null, %struct.Curl_tree** %smaller, align 8, !dbg !326
  br label %if.end77, !dbg !327

if.else:                                          ; preds = %if.end33
  %tv_sec36 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !328
  %40 = load i64, i64* %tv_sec36, align 8, !dbg !328
  %41 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !328
  %key37 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %41, i32 0, i32 4, !dbg !328
  %tv_sec38 = getelementptr inbounds %struct.timeval, %struct.timeval* %key37, i32 0, i32 0, !dbg !328
  %42 = load i64, i64* %tv_sec38, align 8, !dbg !328
  %cmp39 = icmp slt i64 %40, %42, !dbg !328
  br i1 %cmp39, label %cond.true40, label %cond.false41, !dbg !328

cond.true40:                                      ; preds = %if.else
  br label %cond.end63, !dbg !330

cond.false41:                                     ; preds = %if.else
  %tv_sec42 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !332
  %43 = load i64, i64* %tv_sec42, align 8, !dbg !332
  %44 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !332
  %key43 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %44, i32 0, i32 4, !dbg !332
  %tv_sec44 = getelementptr inbounds %struct.timeval, %struct.timeval* %key43, i32 0, i32 0, !dbg !332
  %45 = load i64, i64* %tv_sec44, align 8, !dbg !332
  %cmp45 = icmp sgt i64 %43, %45, !dbg !332
  br i1 %cmp45, label %cond.true46, label %cond.false47, !dbg !332

cond.true46:                                      ; preds = %cond.false41
  br label %cond.end61, !dbg !334

cond.false47:                                     ; preds = %cond.false41
  %tv_usec48 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !336
  %46 = load i64, i64* %tv_usec48, align 8, !dbg !336
  %47 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !336
  %key49 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %47, i32 0, i32 4, !dbg !336
  %tv_usec50 = getelementptr inbounds %struct.timeval, %struct.timeval* %key49, i32 0, i32 1, !dbg !336
  %48 = load i64, i64* %tv_usec50, align 8, !dbg !336
  %cmp51 = icmp slt i64 %46, %48, !dbg !336
  br i1 %cmp51, label %cond.true52, label %cond.false53, !dbg !336

cond.true52:                                      ; preds = %cond.false47
  br label %cond.end59, !dbg !338

cond.false53:                                     ; preds = %cond.false47
  %tv_usec54 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !340
  %49 = load i64, i64* %tv_usec54, align 8, !dbg !340
  %50 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !340
  %key55 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %50, i32 0, i32 4, !dbg !340
  %tv_usec56 = getelementptr inbounds %struct.timeval, %struct.timeval* %key55, i32 0, i32 1, !dbg !340
  %51 = load i64, i64* %tv_usec56, align 8, !dbg !340
  %cmp57 = icmp sgt i64 %49, %51, !dbg !340
  %cond58 = select i1 %cmp57, i32 1, i32 0, !dbg !340
  br label %cond.end59, !dbg !340

cond.end59:                                       ; preds = %cond.false53, %cond.true52
  %cond60 = phi i32 [ -1, %cond.true52 ], [ %cond58, %cond.false53 ], !dbg !342
  br label %cond.end61, !dbg !342

cond.end61:                                       ; preds = %cond.end59, %cond.true46
  %cond62 = phi i32 [ 1, %cond.true46 ], [ %cond60, %cond.end59 ], !dbg !344
  br label %cond.end63, !dbg !344

cond.end63:                                       ; preds = %cond.end61, %cond.true40
  %cond64 = phi i32 [ -1, %cond.true40 ], [ %cond62, %cond.end61 ], !dbg !346
  %cmp65 = icmp slt i32 %cond64, 0, !dbg !348
  br i1 %cmp65, label %if.then66, label %if.else71, !dbg !346

if.then66:                                        ; preds = %cond.end63
  %52 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !349
  %smaller67 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %52, i32 0, i32 0, !dbg !351
  %53 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller67, align 8, !dbg !351
  %54 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !352
  %smaller68 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %54, i32 0, i32 0, !dbg !353
  store %struct.Curl_tree* %53, %struct.Curl_tree** %smaller68, align 8, !dbg !354
  %55 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !355
  %56 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !356
  %larger69 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %56, i32 0, i32 1, !dbg !357
  store %struct.Curl_tree* %55, %struct.Curl_tree** %larger69, align 8, !dbg !358
  %57 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !359
  %smaller70 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %57, i32 0, i32 0, !dbg !360
  store %struct.Curl_tree* null, %struct.Curl_tree** %smaller70, align 8, !dbg !361
  br label %if.end76, !dbg !362

if.else71:                                        ; preds = %cond.end63
  %58 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !363
  %larger72 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %58, i32 0, i32 1, !dbg !365
  %59 = load %struct.Curl_tree*, %struct.Curl_tree** %larger72, align 8, !dbg !365
  %60 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !366
  %larger73 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %60, i32 0, i32 1, !dbg !367
  store %struct.Curl_tree* %59, %struct.Curl_tree** %larger73, align 8, !dbg !368
  %61 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !369
  %62 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !370
  %smaller74 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %62, i32 0, i32 0, !dbg !371
  store %struct.Curl_tree* %61, %struct.Curl_tree** %smaller74, align 8, !dbg !372
  %63 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !373
  %larger75 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %63, i32 0, i32 1, !dbg !374
  store %struct.Curl_tree* null, %struct.Curl_tree** %larger75, align 8, !dbg !375
  br label %if.end76

if.end76:                                         ; preds = %if.else71, %if.then66
  br label %if.end77

if.end77:                                         ; preds = %if.end76, %if.then35
  %64 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !376
  %key78 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %64, i32 0, i32 4, !dbg !377
  %65 = bitcast %struct.timeval* %key78 to i8*, !dbg !378
  %66 = bitcast %struct.timeval* %i to i8*, !dbg !378
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %65, i8* %66, i64 16, i32 8, i1 false), !dbg !378
  %67 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !379
  %68 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !380
  %samen79 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %68, i32 0, i32 2, !dbg !381
  store %struct.Curl_tree* %67, %struct.Curl_tree** %samen79, align 8, !dbg !382
  %69 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !383
  %70 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !384
  %samep80 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %70, i32 0, i32 3, !dbg !385
  store %struct.Curl_tree* %69, %struct.Curl_tree** %samep80, align 8, !dbg !386
  %71 = load %struct.Curl_tree*, %struct.Curl_tree** %node.addr, align 8, !dbg !387
  store %struct.Curl_tree* %71, %struct.Curl_tree** %retval, align 8, !dbg !388
  br label %return, !dbg !388

return:                                           ; preds = %if.end77, %if.then26, %if.then
  %72 = load %struct.Curl_tree*, %struct.Curl_tree** %retval, align 8, !dbg !389
  ret %struct.Curl_tree* %72, !dbg !389
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

; Function Attrs: nounwind uwtable
define %struct.Curl_tree* @Curl_splaygetbest(i64 %i.coerce0, i64 %i.coerce1, %struct.Curl_tree* %t, %struct.Curl_tree** %removed) #0 !dbg !31 {
entry:
  %retval = alloca %struct.Curl_tree*, align 8
  %i = alloca %struct.timeval, align 8
  %t.addr = alloca %struct.Curl_tree*, align 8
  %removed.addr = alloca %struct.Curl_tree**, align 8
  %x = alloca %struct.Curl_tree*, align 8
  %0 = bitcast %struct.timeval* %i to { i64, i64 }*
  %1 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 0
  store i64 %i.coerce0, i64* %1, align 8
  %2 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %0, i32 0, i32 1
  store i64 %i.coerce1, i64* %2, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval* %i, metadata !390, metadata !48), !dbg !391
  store %struct.Curl_tree* %t, %struct.Curl_tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %t.addr, metadata !392, metadata !48), !dbg !393
  store %struct.Curl_tree** %removed, %struct.Curl_tree*** %removed.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree*** %removed.addr, metadata !394, metadata !48), !dbg !395
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %x, metadata !396, metadata !48), !dbg !397
  %3 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !398
  %tobool = icmp ne %struct.Curl_tree* %3, null, !dbg !398
  br i1 %tobool, label %if.end, label %if.then, !dbg !400

if.then:                                          ; preds = %entry
  %4 = load %struct.Curl_tree**, %struct.Curl_tree*** %removed.addr, align 8, !dbg !401
  store %struct.Curl_tree* null, %struct.Curl_tree** %4, align 8, !dbg !403
  store %struct.Curl_tree* null, %struct.Curl_tree** %retval, align 8, !dbg !404
  br label %return, !dbg !404

if.end:                                           ; preds = %entry
  %5 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !405
  %6 = load i64, i64* getelementptr inbounds ({ i64, i64 }, { i64, i64 }* bitcast (%struct.timeval* @Curl_splaygetbest.tv_zero to { i64, i64 }*), i32 0, i32 0), align 8, !dbg !406
  %7 = load i64, i64* getelementptr inbounds ({ i64, i64 }, { i64, i64 }* bitcast (%struct.timeval* @Curl_splaygetbest.tv_zero to { i64, i64 }*), i32 0, i32 1), align 8, !dbg !406
  %call = call %struct.Curl_tree* @Curl_splay(i64 %6, i64 %7, %struct.Curl_tree* %5), !dbg !406
  store %struct.Curl_tree* %call, %struct.Curl_tree** %t.addr, align 8, !dbg !407
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !408
  %8 = load i64, i64* %tv_sec, align 8, !dbg !408
  %9 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !408
  %key = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %9, i32 0, i32 4, !dbg !408
  %tv_sec1 = getelementptr inbounds %struct.timeval, %struct.timeval* %key, i32 0, i32 0, !dbg !408
  %10 = load i64, i64* %tv_sec1, align 8, !dbg !408
  %cmp = icmp slt i64 %8, %10, !dbg !408
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !408

cond.true:                                        ; preds = %if.end
  br label %cond.end20, !dbg !410

cond.false:                                       ; preds = %if.end
  %tv_sec2 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 0, !dbg !412
  %11 = load i64, i64* %tv_sec2, align 8, !dbg !412
  %12 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !412
  %key3 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %12, i32 0, i32 4, !dbg !412
  %tv_sec4 = getelementptr inbounds %struct.timeval, %struct.timeval* %key3, i32 0, i32 0, !dbg !412
  %13 = load i64, i64* %tv_sec4, align 8, !dbg !412
  %cmp5 = icmp sgt i64 %11, %13, !dbg !412
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !412

cond.true6:                                       ; preds = %cond.false
  br label %cond.end18, !dbg !414

cond.false7:                                      ; preds = %cond.false
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !416
  %14 = load i64, i64* %tv_usec, align 8, !dbg !416
  %15 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !416
  %key8 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %15, i32 0, i32 4, !dbg !416
  %tv_usec9 = getelementptr inbounds %struct.timeval, %struct.timeval* %key8, i32 0, i32 1, !dbg !416
  %16 = load i64, i64* %tv_usec9, align 8, !dbg !416
  %cmp10 = icmp slt i64 %14, %16, !dbg !416
  br i1 %cmp10, label %cond.true11, label %cond.false12, !dbg !416

cond.true11:                                      ; preds = %cond.false7
  br label %cond.end, !dbg !418

cond.false12:                                     ; preds = %cond.false7
  %tv_usec13 = getelementptr inbounds %struct.timeval, %struct.timeval* %i, i32 0, i32 1, !dbg !420
  %17 = load i64, i64* %tv_usec13, align 8, !dbg !420
  %18 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !420
  %key14 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %18, i32 0, i32 4, !dbg !420
  %tv_usec15 = getelementptr inbounds %struct.timeval, %struct.timeval* %key14, i32 0, i32 1, !dbg !420
  %19 = load i64, i64* %tv_usec15, align 8, !dbg !420
  %cmp16 = icmp sgt i64 %17, %19, !dbg !420
  %cond = select i1 %cmp16, i32 1, i32 0, !dbg !420
  br label %cond.end, !dbg !420

cond.end:                                         ; preds = %cond.false12, %cond.true11
  %cond17 = phi i32 [ -1, %cond.true11 ], [ %cond, %cond.false12 ], !dbg !422
  br label %cond.end18, !dbg !422

cond.end18:                                       ; preds = %cond.end, %cond.true6
  %cond19 = phi i32 [ 1, %cond.true6 ], [ %cond17, %cond.end ], !dbg !424
  br label %cond.end20, !dbg !424

cond.end20:                                       ; preds = %cond.end18, %cond.true
  %cond21 = phi i32 [ -1, %cond.true ], [ %cond19, %cond.end18 ], !dbg !426
  %cmp22 = icmp slt i32 %cond21, 0, !dbg !428
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !426

if.then23:                                        ; preds = %cond.end20
  %20 = load %struct.Curl_tree**, %struct.Curl_tree*** %removed.addr, align 8, !dbg !429
  store %struct.Curl_tree* null, %struct.Curl_tree** %20, align 8, !dbg !431
  %21 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !432
  store %struct.Curl_tree* %21, %struct.Curl_tree** %retval, align 8, !dbg !433
  br label %return, !dbg !433

if.end24:                                         ; preds = %cond.end20
  %22 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !434
  %samen = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %22, i32 0, i32 2, !dbg !435
  %23 = load %struct.Curl_tree*, %struct.Curl_tree** %samen, align 8, !dbg !435
  store %struct.Curl_tree* %23, %struct.Curl_tree** %x, align 8, !dbg !436
  %24 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !437
  %25 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !439
  %cmp25 = icmp ne %struct.Curl_tree* %24, %25, !dbg !440
  br i1 %cmp25, label %if.then26, label %if.end34, !dbg !441

if.then26:                                        ; preds = %if.end24
  %26 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !442
  %key27 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %26, i32 0, i32 4, !dbg !444
  %27 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !445
  %key28 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %27, i32 0, i32 4, !dbg !446
  %28 = bitcast %struct.timeval* %key27 to i8*, !dbg !446
  %29 = bitcast %struct.timeval* %key28 to i8*, !dbg !446
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %28, i8* %29, i64 16, i32 8, i1 false), !dbg !446
  %30 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !447
  %larger = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %30, i32 0, i32 1, !dbg !448
  %31 = load %struct.Curl_tree*, %struct.Curl_tree** %larger, align 8, !dbg !448
  %32 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !449
  %larger29 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %32, i32 0, i32 1, !dbg !450
  store %struct.Curl_tree* %31, %struct.Curl_tree** %larger29, align 8, !dbg !451
  %33 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !452
  %smaller = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %33, i32 0, i32 0, !dbg !453
  %34 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller, align 8, !dbg !453
  %35 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !454
  %smaller30 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %35, i32 0, i32 0, !dbg !455
  store %struct.Curl_tree* %34, %struct.Curl_tree** %smaller30, align 8, !dbg !456
  %36 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !457
  %samep = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %36, i32 0, i32 3, !dbg !458
  %37 = load %struct.Curl_tree*, %struct.Curl_tree** %samep, align 8, !dbg !458
  %38 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !459
  %samep31 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %38, i32 0, i32 3, !dbg !460
  store %struct.Curl_tree* %37, %struct.Curl_tree** %samep31, align 8, !dbg !461
  %39 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !462
  %40 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !463
  %samep32 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %40, i32 0, i32 3, !dbg !464
  %41 = load %struct.Curl_tree*, %struct.Curl_tree** %samep32, align 8, !dbg !464
  %samen33 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %41, i32 0, i32 2, !dbg !465
  store %struct.Curl_tree* %39, %struct.Curl_tree** %samen33, align 8, !dbg !466
  %42 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !467
  %43 = load %struct.Curl_tree**, %struct.Curl_tree*** %removed.addr, align 8, !dbg !468
  store %struct.Curl_tree* %42, %struct.Curl_tree** %43, align 8, !dbg !469
  %44 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !470
  store %struct.Curl_tree* %44, %struct.Curl_tree** %retval, align 8, !dbg !471
  br label %return, !dbg !471

if.end34:                                         ; preds = %if.end24
  %45 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !472
  %larger35 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %45, i32 0, i32 1, !dbg !473
  %46 = load %struct.Curl_tree*, %struct.Curl_tree** %larger35, align 8, !dbg !473
  store %struct.Curl_tree* %46, %struct.Curl_tree** %x, align 8, !dbg !474
  %47 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !475
  %48 = load %struct.Curl_tree**, %struct.Curl_tree*** %removed.addr, align 8, !dbg !476
  store %struct.Curl_tree* %47, %struct.Curl_tree** %48, align 8, !dbg !477
  %49 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !478
  store %struct.Curl_tree* %49, %struct.Curl_tree** %retval, align 8, !dbg !479
  br label %return, !dbg !479

return:                                           ; preds = %if.end34, %if.then26, %if.then23, %if.then
  %50 = load %struct.Curl_tree*, %struct.Curl_tree** %retval, align 8, !dbg !480
  ret %struct.Curl_tree* %50, !dbg !480
}

; Function Attrs: nounwind uwtable
define i32 @Curl_splayremovebyaddr(%struct.Curl_tree* %t, %struct.Curl_tree* %removenode, %struct.Curl_tree** %newroot) #0 !dbg !35 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.Curl_tree*, align 8
  %removenode.addr = alloca %struct.Curl_tree*, align 8
  %newroot.addr = alloca %struct.Curl_tree**, align 8
  %x = alloca %struct.Curl_tree*, align 8
  store %struct.Curl_tree* %t, %struct.Curl_tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %t.addr, metadata !481, metadata !48), !dbg !482
  store %struct.Curl_tree* %removenode, %struct.Curl_tree** %removenode.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %removenode.addr, metadata !483, metadata !48), !dbg !484
  store %struct.Curl_tree** %newroot, %struct.Curl_tree*** %newroot.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_tree*** %newroot.addr, metadata !485, metadata !48), !dbg !486
  call void @llvm.dbg.declare(metadata %struct.Curl_tree** %x, metadata !487, metadata !48), !dbg !488
  %0 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !489
  %tobool = icmp ne %struct.Curl_tree* %0, null, !dbg !489
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !491

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !492
  %tobool1 = icmp ne %struct.Curl_tree* %1, null, !dbg !492
  br i1 %tobool1, label %if.end, label %if.then, !dbg !494

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 1, i32* %retval, align 4, !dbg !495
  br label %return, !dbg !495

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i64, i64* getelementptr inbounds (%struct.timeval, %struct.timeval* @Curl_splayremovebyaddr.KEY_NOTUSED, i32 0, i32 0), align 8, !dbg !496
  %3 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !496
  %key = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %3, i32 0, i32 4, !dbg !496
  %tv_sec = getelementptr inbounds %struct.timeval, %struct.timeval* %key, i32 0, i32 0, !dbg !496
  %4 = load i64, i64* %tv_sec, align 8, !dbg !496
  %cmp = icmp slt i64 %2, %4, !dbg !496
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !496

cond.true:                                        ; preds = %if.end
  br label %cond.end17, !dbg !498

cond.false:                                       ; preds = %if.end
  %5 = load i64, i64* getelementptr inbounds (%struct.timeval, %struct.timeval* @Curl_splayremovebyaddr.KEY_NOTUSED, i32 0, i32 0), align 8, !dbg !500
  %6 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !500
  %key2 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %6, i32 0, i32 4, !dbg !500
  %tv_sec3 = getelementptr inbounds %struct.timeval, %struct.timeval* %key2, i32 0, i32 0, !dbg !500
  %7 = load i64, i64* %tv_sec3, align 8, !dbg !500
  %cmp4 = icmp sgt i64 %5, %7, !dbg !500
  br i1 %cmp4, label %cond.true5, label %cond.false6, !dbg !500

cond.true5:                                       ; preds = %cond.false
  br label %cond.end15, !dbg !502

cond.false6:                                      ; preds = %cond.false
  %8 = load i64, i64* getelementptr inbounds (%struct.timeval, %struct.timeval* @Curl_splayremovebyaddr.KEY_NOTUSED, i32 0, i32 1), align 8, !dbg !504
  %9 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !504
  %key7 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %9, i32 0, i32 4, !dbg !504
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %key7, i32 0, i32 1, !dbg !504
  %10 = load i64, i64* %tv_usec, align 8, !dbg !504
  %cmp8 = icmp slt i64 %8, %10, !dbg !504
  br i1 %cmp8, label %cond.true9, label %cond.false10, !dbg !504

cond.true9:                                       ; preds = %cond.false6
  br label %cond.end, !dbg !506

cond.false10:                                     ; preds = %cond.false6
  %11 = load i64, i64* getelementptr inbounds (%struct.timeval, %struct.timeval* @Curl_splayremovebyaddr.KEY_NOTUSED, i32 0, i32 1), align 8, !dbg !508
  %12 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !508
  %key11 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %12, i32 0, i32 4, !dbg !508
  %tv_usec12 = getelementptr inbounds %struct.timeval, %struct.timeval* %key11, i32 0, i32 1, !dbg !508
  %13 = load i64, i64* %tv_usec12, align 8, !dbg !508
  %cmp13 = icmp sgt i64 %11, %13, !dbg !508
  %cond = select i1 %cmp13, i32 1, i32 0, !dbg !508
  br label %cond.end, !dbg !508

cond.end:                                         ; preds = %cond.false10, %cond.true9
  %cond14 = phi i32 [ -1, %cond.true9 ], [ %cond, %cond.false10 ], !dbg !510
  br label %cond.end15, !dbg !510

cond.end15:                                       ; preds = %cond.end, %cond.true5
  %cond16 = phi i32 [ 1, %cond.true5 ], [ %cond14, %cond.end ], !dbg !512
  br label %cond.end17, !dbg !512

cond.end17:                                       ; preds = %cond.end15, %cond.true
  %cond18 = phi i32 [ -1, %cond.true ], [ %cond16, %cond.end15 ], !dbg !514
  %cmp19 = icmp eq i32 %cond18, 0, !dbg !516
  br i1 %cmp19, label %if.then20, label %if.end30, !dbg !514

if.then20:                                        ; preds = %cond.end17
  %14 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !517
  %samen = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %14, i32 0, i32 2, !dbg !520
  %15 = load %struct.Curl_tree*, %struct.Curl_tree** %samen, align 8, !dbg !520
  %16 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !521
  %cmp21 = icmp eq %struct.Curl_tree* %15, %16, !dbg !522
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !523

if.then22:                                        ; preds = %if.then20
  store i32 3, i32* %retval, align 4, !dbg !524
  br label %return, !dbg !524

if.end23:                                         ; preds = %if.then20
  %17 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !525
  %samen24 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %17, i32 0, i32 2, !dbg !526
  %18 = load %struct.Curl_tree*, %struct.Curl_tree** %samen24, align 8, !dbg !526
  %19 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !527
  %samep = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %19, i32 0, i32 3, !dbg !528
  %20 = load %struct.Curl_tree*, %struct.Curl_tree** %samep, align 8, !dbg !528
  %samen25 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %20, i32 0, i32 2, !dbg !529
  store %struct.Curl_tree* %18, %struct.Curl_tree** %samen25, align 8, !dbg !530
  %21 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !531
  %samep26 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %21, i32 0, i32 3, !dbg !532
  %22 = load %struct.Curl_tree*, %struct.Curl_tree** %samep26, align 8, !dbg !532
  %23 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !533
  %samen27 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %23, i32 0, i32 2, !dbg !534
  %24 = load %struct.Curl_tree*, %struct.Curl_tree** %samen27, align 8, !dbg !534
  %samep28 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %24, i32 0, i32 3, !dbg !535
  store %struct.Curl_tree* %22, %struct.Curl_tree** %samep28, align 8, !dbg !536
  %25 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !537
  %26 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !538
  %samen29 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %26, i32 0, i32 2, !dbg !539
  store %struct.Curl_tree* %25, %struct.Curl_tree** %samen29, align 8, !dbg !540
  %27 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !541
  %28 = load %struct.Curl_tree**, %struct.Curl_tree*** %newroot.addr, align 8, !dbg !542
  store %struct.Curl_tree* %27, %struct.Curl_tree** %28, align 8, !dbg !543
  store i32 0, i32* %retval, align 4, !dbg !544
  br label %return, !dbg !544

if.end30:                                         ; preds = %cond.end17
  %29 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !545
  %key31 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %29, i32 0, i32 4, !dbg !546
  %30 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !547
  %31 = bitcast %struct.timeval* %key31 to { i64, i64 }*, !dbg !548
  %32 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 0, !dbg !548
  %33 = load i64, i64* %32, align 8, !dbg !548
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %31, i32 0, i32 1, !dbg !548
  %35 = load i64, i64* %34, align 8, !dbg !548
  %call = call %struct.Curl_tree* @Curl_splay(i64 %33, i64 %35, %struct.Curl_tree* %30), !dbg !548
  store %struct.Curl_tree* %call, %struct.Curl_tree** %t.addr, align 8, !dbg !549
  %36 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !550
  %37 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !552
  %cmp32 = icmp ne %struct.Curl_tree* %36, %37, !dbg !553
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !554

if.then33:                                        ; preds = %if.end30
  store i32 2, i32* %retval, align 4, !dbg !555
  br label %return, !dbg !555

if.end34:                                         ; preds = %if.end30
  %38 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !556
  %samen35 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %38, i32 0, i32 2, !dbg !557
  %39 = load %struct.Curl_tree*, %struct.Curl_tree** %samen35, align 8, !dbg !557
  store %struct.Curl_tree* %39, %struct.Curl_tree** %x, align 8, !dbg !558
  %40 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !559
  %41 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !561
  %cmp36 = icmp ne %struct.Curl_tree* %40, %41, !dbg !562
  br i1 %cmp36, label %if.then37, label %if.else, !dbg !563

if.then37:                                        ; preds = %if.end34
  %42 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !564
  %key38 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %42, i32 0, i32 4, !dbg !566
  %43 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !567
  %key39 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %43, i32 0, i32 4, !dbg !568
  %44 = bitcast %struct.timeval* %key38 to i8*, !dbg !568
  %45 = bitcast %struct.timeval* %key39 to i8*, !dbg !568
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %44, i8* %45, i64 16, i32 8, i1 false), !dbg !568
  %46 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !569
  %larger = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %46, i32 0, i32 1, !dbg !570
  %47 = load %struct.Curl_tree*, %struct.Curl_tree** %larger, align 8, !dbg !570
  %48 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !571
  %larger40 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %48, i32 0, i32 1, !dbg !572
  store %struct.Curl_tree* %47, %struct.Curl_tree** %larger40, align 8, !dbg !573
  %49 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !574
  %smaller = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %49, i32 0, i32 0, !dbg !575
  %50 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller, align 8, !dbg !575
  %51 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !576
  %smaller41 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %51, i32 0, i32 0, !dbg !577
  store %struct.Curl_tree* %50, %struct.Curl_tree** %smaller41, align 8, !dbg !578
  %52 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !579
  %samep42 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %52, i32 0, i32 3, !dbg !580
  %53 = load %struct.Curl_tree*, %struct.Curl_tree** %samep42, align 8, !dbg !580
  %54 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !581
  %samep43 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %54, i32 0, i32 3, !dbg !582
  store %struct.Curl_tree* %53, %struct.Curl_tree** %samep43, align 8, !dbg !583
  %55 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !584
  %56 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !585
  %samep44 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %56, i32 0, i32 3, !dbg !586
  %57 = load %struct.Curl_tree*, %struct.Curl_tree** %samep44, align 8, !dbg !586
  %samen45 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %57, i32 0, i32 2, !dbg !587
  store %struct.Curl_tree* %55, %struct.Curl_tree** %samen45, align 8, !dbg !588
  br label %if.end57, !dbg !589

if.else:                                          ; preds = %if.end34
  %58 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !590
  %smaller46 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %58, i32 0, i32 0, !dbg !593
  %59 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller46, align 8, !dbg !593
  %cmp47 = icmp eq %struct.Curl_tree* %59, null, !dbg !594
  br i1 %cmp47, label %if.then48, label %if.else50, !dbg !595

if.then48:                                        ; preds = %if.else
  %60 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !596
  %larger49 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %60, i32 0, i32 1, !dbg !597
  %61 = load %struct.Curl_tree*, %struct.Curl_tree** %larger49, align 8, !dbg !597
  store %struct.Curl_tree* %61, %struct.Curl_tree** %x, align 8, !dbg !598
  br label %if.end56, !dbg !599

if.else50:                                        ; preds = %if.else
  %62 = load %struct.Curl_tree*, %struct.Curl_tree** %removenode.addr, align 8, !dbg !600
  %key51 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %62, i32 0, i32 4, !dbg !602
  %63 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !603
  %smaller52 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %63, i32 0, i32 0, !dbg !604
  %64 = load %struct.Curl_tree*, %struct.Curl_tree** %smaller52, align 8, !dbg !604
  %65 = bitcast %struct.timeval* %key51 to { i64, i64 }*, !dbg !605
  %66 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %65, i32 0, i32 0, !dbg !605
  %67 = load i64, i64* %66, align 8, !dbg !605
  %68 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %65, i32 0, i32 1, !dbg !605
  %69 = load i64, i64* %68, align 8, !dbg !605
  %call53 = call %struct.Curl_tree* @Curl_splay(i64 %67, i64 %69, %struct.Curl_tree* %64), !dbg !605
  store %struct.Curl_tree* %call53, %struct.Curl_tree** %x, align 8, !dbg !606
  %70 = load %struct.Curl_tree*, %struct.Curl_tree** %t.addr, align 8, !dbg !607
  %larger54 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %70, i32 0, i32 1, !dbg !608
  %71 = load %struct.Curl_tree*, %struct.Curl_tree** %larger54, align 8, !dbg !608
  %72 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !609
  %larger55 = getelementptr inbounds %struct.Curl_tree, %struct.Curl_tree* %72, i32 0, i32 1, !dbg !610
  store %struct.Curl_tree* %71, %struct.Curl_tree** %larger55, align 8, !dbg !611
  br label %if.end56

if.end56:                                         ; preds = %if.else50, %if.then48
  br label %if.end57

if.end57:                                         ; preds = %if.end56, %if.then37
  %73 = load %struct.Curl_tree*, %struct.Curl_tree** %x, align 8, !dbg !612
  %74 = load %struct.Curl_tree**, %struct.Curl_tree*** %newroot.addr, align 8, !dbg !613
  store %struct.Curl_tree* %73, %struct.Curl_tree** %74, align 8, !dbg !614
  store i32 0, i32* %retval, align 4, !dbg !615
  br label %return, !dbg !615

return:                                           ; preds = %if.end57, %if.then33, %if.end23, %if.then22, %if.then
  %75 = load i32, i32* %retval, align 4, !dbg !616
  ret i32 %75, !dbg !616
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!44, !45}
!llvm.ident = !{!46}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !39)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !28, !31, !35}
!6 = distinct !DISubprogram(name: "Curl_splay", scope: !1, file: !1, line: 40, type: !7, isLocal: false, isDefinition: true, scopeLine: 42, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !18, !9}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_tree", file: !11, line: 26, size: 448, align: 64, elements: !12)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!12 = !{!13, !14, !15, !16, !17, !27}
!13 = !DIDerivedType(tag: DW_TAG_member, name: "smaller", scope: !10, file: !11, line: 27, baseType: !9, size: 64, align: 64)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "larger", scope: !10, file: !11, line: 28, baseType: !9, size: 64, align: 64, offset: 64)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "samen", scope: !10, file: !11, line: 29, baseType: !9, size: 64, align: 64, offset: 128)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "samep", scope: !10, file: !11, line: 30, baseType: !9, size: 64, align: 64, offset: 192)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !10, file: !11, line: 31, baseType: !18, size: 128, align: 64, offset: 256)
!18 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !19, line: 30, size: 128, align: 64, elements: !20)
!19 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!20 = !{!21, !25}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !18, file: !19, line: 32, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !23, line: 139, baseType: !24)
!23 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!24 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !18, file: !19, line: 33, baseType: !26, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !23, line: 141, baseType: !24)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "payload", scope: !10, file: !11, line: 32, baseType: !4, size: 64, align: 64, offset: 384)
!28 = distinct !DISubprogram(name: "Curl_splayinsert", scope: !1, file: !1, line: 100, type: !29, isLocal: false, isDefinition: true, scopeLine: 103, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!29 = !DISubroutineType(types: !30)
!30 = !{!9, !18, !9, !9}
!31 = distinct !DISubprogram(name: "Curl_splaygetbest", scope: !1, file: !1, line: 152, type: !32, isLocal: false, isDefinition: true, scopeLine: 155, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!32 = !DISubroutineType(types: !33)
!33 = !{!9, !18, !9, !34}
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!35 = distinct !DISubprogram(name: "Curl_splayremovebyaddr", scope: !1, file: !1, line: 208, type: !36, isLocal: false, isDefinition: true, scopeLine: 211, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !9, !9, !34}
!38 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!39 = !{!40, !42, !43}
!40 = !DIGlobalVariable(name: "KEY_NOTUSED", scope: !28, file: !1, line: 104, type: !41, isLocal: true, isDefinition: true, variable: %struct.timeval* @Curl_splayinsert.KEY_NOTUSED)
!41 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !18)
!42 = !DIGlobalVariable(name: "tv_zero", scope: !31, file: !1, line: 156, type: !18, isLocal: true, isDefinition: true, variable: %struct.timeval* @Curl_splaygetbest.tv_zero)
!43 = !DIGlobalVariable(name: "KEY_NOTUSED", scope: !35, file: !1, line: 212, type: !41, isLocal: true, isDefinition: true, variable: %struct.timeval* @Curl_splayremovebyaddr.KEY_NOTUSED)
!44 = !{i32 2, !"Dwarf Version", i32 4}
!45 = !{i32 2, !"Debug Info Version", i32 3}
!46 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!47 = !DILocalVariable(name: "i", arg: 1, scope: !6, file: !1, line: 40, type: !18)
!48 = !DIExpression()
!49 = !DILocation(line: 40, column: 45, scope: !6)
!50 = !DILocalVariable(name: "t", arg: 2, scope: !6, file: !1, line: 41, type: !9)
!51 = !DILocation(line: 41, column: 48, scope: !6)
!52 = !DILocalVariable(name: "N", scope: !6, file: !1, line: 43, type: !10)
!53 = !DILocation(line: 43, column: 20, scope: !6)
!54 = !DILocalVariable(name: "l", scope: !6, file: !1, line: 43, type: !9)
!55 = !DILocation(line: 43, column: 24, scope: !6)
!56 = !DILocalVariable(name: "r", scope: !6, file: !1, line: 43, type: !9)
!57 = !DILocation(line: 43, column: 28, scope: !6)
!58 = !DILocalVariable(name: "y", scope: !6, file: !1, line: 43, type: !9)
!59 = !DILocation(line: 43, column: 32, scope: !6)
!60 = !DILocalVariable(name: "comp", scope: !6, file: !1, line: 44, type: !24)
!61 = !DILocation(line: 44, column: 8, scope: !6)
!62 = !DILocation(line: 46, column: 6, scope: !63)
!63 = distinct !DILexicalBlock(scope: !6, file: !1, line: 46, column: 6)
!64 = !DILocation(line: 46, column: 8, scope: !63)
!65 = !DILocation(line: 46, column: 6, scope: !6)
!66 = !DILocation(line: 47, column: 12, scope: !63)
!67 = !DILocation(line: 47, column: 5, scope: !63)
!68 = !DILocation(line: 48, column: 17, scope: !6)
!69 = !DILocation(line: 48, column: 24, scope: !6)
!70 = !DILocation(line: 48, column: 5, scope: !6)
!71 = !DILocation(line: 48, column: 13, scope: !6)
!72 = !DILocation(line: 49, column: 9, scope: !6)
!73 = !DILocation(line: 49, column: 5, scope: !6)
!74 = !DILocation(line: 51, column: 3, scope: !6)
!75 = !DILocation(line: 52, column: 12, scope: !76)
!76 = distinct !DILexicalBlock(scope: !77, file: !1, line: 51, column: 11)
!77 = distinct !DILexicalBlock(scope: !78, file: !1, line: 51, column: 3)
!78 = distinct !DILexicalBlock(scope: !6, file: !1, line: 51, column: 3)
!79 = !DILocation(line: 52, column: 12, scope: !80)
!80 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 1)
!81 = !DILocation(line: 52, column: 12, scope: !82)
!82 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 2)
!83 = !DILocation(line: 52, column: 12, scope: !84)
!84 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 3)
!85 = !DILocation(line: 52, column: 12, scope: !86)
!86 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 4)
!87 = !DILocation(line: 52, column: 12, scope: !88)
!88 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 5)
!89 = !DILocation(line: 52, column: 12, scope: !90)
!90 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 6)
!91 = !DILocation(line: 52, column: 12, scope: !92)
!92 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 7)
!93 = !DILocation(line: 52, column: 12, scope: !94)
!94 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 8)
!95 = !DILocation(line: 52, column: 12, scope: !96)
!96 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 9)
!97 = !DILocation(line: 52, column: 10, scope: !96)
!98 = !DILocation(line: 53, column: 8, scope: !99)
!99 = distinct !DILexicalBlock(scope: !76, file: !1, line: 53, column: 8)
!100 = !DILocation(line: 53, column: 13, scope: !99)
!101 = !DILocation(line: 53, column: 8, scope: !76)
!102 = !DILocation(line: 54, column: 10, scope: !103)
!103 = distinct !DILexicalBlock(scope: !104, file: !1, line: 54, column: 10)
!104 = distinct !DILexicalBlock(scope: !99, file: !1, line: 53, column: 18)
!105 = !DILocation(line: 54, column: 13, scope: !103)
!106 = !DILocation(line: 54, column: 21, scope: !103)
!107 = !DILocation(line: 54, column: 10, scope: !104)
!108 = !DILocation(line: 55, column: 9, scope: !103)
!109 = !DILocation(line: 56, column: 10, scope: !110)
!110 = distinct !DILexicalBlock(scope: !104, file: !1, line: 56, column: 10)
!111 = !DILocation(line: 56, column: 10, scope: !112)
!112 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 1)
!113 = !DILocation(line: 56, column: 10, scope: !114)
!114 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 2)
!115 = !DILocation(line: 56, column: 10, scope: !116)
!116 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 3)
!117 = !DILocation(line: 56, column: 10, scope: !118)
!118 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 4)
!119 = !DILocation(line: 56, column: 10, scope: !120)
!120 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 5)
!121 = !DILocation(line: 56, column: 10, scope: !122)
!122 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 6)
!123 = !DILocation(line: 56, column: 10, scope: !124)
!124 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 7)
!125 = !DILocation(line: 56, column: 10, scope: !126)
!126 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 8)
!127 = !DILocation(line: 56, column: 10, scope: !128)
!128 = !DILexicalBlockFile(scope: !110, file: !1, discriminator: 9)
!129 = !DILocation(line: 56, column: 38, scope: !128)
!130 = !DILocation(line: 57, column: 13, scope: !131)
!131 = distinct !DILexicalBlock(scope: !110, file: !1, line: 56, column: 43)
!132 = !DILocation(line: 57, column: 16, scope: !131)
!133 = !DILocation(line: 57, column: 11, scope: !131)
!134 = !DILocation(line: 58, column: 22, scope: !131)
!135 = !DILocation(line: 58, column: 25, scope: !131)
!136 = !DILocation(line: 58, column: 9, scope: !131)
!137 = !DILocation(line: 58, column: 12, scope: !131)
!138 = !DILocation(line: 58, column: 20, scope: !131)
!139 = !DILocation(line: 59, column: 21, scope: !131)
!140 = !DILocation(line: 59, column: 9, scope: !131)
!141 = !DILocation(line: 59, column: 12, scope: !131)
!142 = !DILocation(line: 59, column: 19, scope: !131)
!143 = !DILocation(line: 60, column: 13, scope: !131)
!144 = !DILocation(line: 60, column: 11, scope: !131)
!145 = !DILocation(line: 61, column: 12, scope: !146)
!146 = distinct !DILexicalBlock(scope: !131, file: !1, line: 61, column: 12)
!147 = !DILocation(line: 61, column: 15, scope: !146)
!148 = !DILocation(line: 61, column: 23, scope: !146)
!149 = !DILocation(line: 61, column: 12, scope: !131)
!150 = !DILocation(line: 62, column: 11, scope: !146)
!151 = !DILocation(line: 63, column: 7, scope: !131)
!152 = !DILocation(line: 64, column: 20, scope: !104)
!153 = !DILocation(line: 64, column: 7, scope: !104)
!154 = !DILocation(line: 64, column: 10, scope: !104)
!155 = !DILocation(line: 64, column: 18, scope: !104)
!156 = !DILocation(line: 65, column: 11, scope: !104)
!157 = !DILocation(line: 65, column: 9, scope: !104)
!158 = !DILocation(line: 66, column: 11, scope: !104)
!159 = !DILocation(line: 66, column: 14, scope: !104)
!160 = !DILocation(line: 66, column: 9, scope: !104)
!161 = !DILocation(line: 67, column: 5, scope: !104)
!162 = !DILocation(line: 68, column: 13, scope: !163)
!163 = distinct !DILexicalBlock(scope: !99, file: !1, line: 68, column: 13)
!164 = !DILocation(line: 68, column: 18, scope: !163)
!165 = !DILocation(line: 68, column: 13, scope: !99)
!166 = !DILocation(line: 69, column: 10, scope: !167)
!167 = distinct !DILexicalBlock(scope: !168, file: !1, line: 69, column: 10)
!168 = distinct !DILexicalBlock(scope: !163, file: !1, line: 68, column: 23)
!169 = !DILocation(line: 69, column: 13, scope: !167)
!170 = !DILocation(line: 69, column: 20, scope: !167)
!171 = !DILocation(line: 69, column: 10, scope: !168)
!172 = !DILocation(line: 70, column: 9, scope: !167)
!173 = !DILocation(line: 71, column: 10, scope: !174)
!174 = distinct !DILexicalBlock(scope: !168, file: !1, line: 71, column: 10)
!175 = !DILocation(line: 71, column: 10, scope: !176)
!176 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 1)
!177 = !DILocation(line: 71, column: 10, scope: !178)
!178 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 2)
!179 = !DILocation(line: 71, column: 10, scope: !180)
!180 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 3)
!181 = !DILocation(line: 71, column: 10, scope: !182)
!182 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 4)
!183 = !DILocation(line: 71, column: 10, scope: !184)
!184 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 5)
!185 = !DILocation(line: 71, column: 10, scope: !186)
!186 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 6)
!187 = !DILocation(line: 71, column: 10, scope: !188)
!188 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 7)
!189 = !DILocation(line: 71, column: 10, scope: !190)
!190 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 8)
!191 = !DILocation(line: 71, column: 10, scope: !192)
!192 = !DILexicalBlockFile(scope: !174, file: !1, discriminator: 9)
!193 = !DILocation(line: 71, column: 37, scope: !192)
!194 = !DILocation(line: 72, column: 13, scope: !195)
!195 = distinct !DILexicalBlock(scope: !174, file: !1, line: 71, column: 42)
!196 = !DILocation(line: 72, column: 16, scope: !195)
!197 = !DILocation(line: 72, column: 11, scope: !195)
!198 = !DILocation(line: 73, column: 21, scope: !195)
!199 = !DILocation(line: 73, column: 24, scope: !195)
!200 = !DILocation(line: 73, column: 9, scope: !195)
!201 = !DILocation(line: 73, column: 12, scope: !195)
!202 = !DILocation(line: 73, column: 19, scope: !195)
!203 = !DILocation(line: 74, column: 22, scope: !195)
!204 = !DILocation(line: 74, column: 9, scope: !195)
!205 = !DILocation(line: 74, column: 12, scope: !195)
!206 = !DILocation(line: 74, column: 20, scope: !195)
!207 = !DILocation(line: 75, column: 13, scope: !195)
!208 = !DILocation(line: 75, column: 11, scope: !195)
!209 = !DILocation(line: 76, column: 12, scope: !210)
!210 = distinct !DILexicalBlock(scope: !195, file: !1, line: 76, column: 12)
!211 = !DILocation(line: 76, column: 15, scope: !210)
!212 = !DILocation(line: 76, column: 22, scope: !210)
!213 = !DILocation(line: 76, column: 12, scope: !195)
!214 = !DILocation(line: 77, column: 11, scope: !210)
!215 = !DILocation(line: 78, column: 7, scope: !195)
!216 = !DILocation(line: 79, column: 19, scope: !168)
!217 = !DILocation(line: 79, column: 7, scope: !168)
!218 = !DILocation(line: 79, column: 10, scope: !168)
!219 = !DILocation(line: 79, column: 17, scope: !168)
!220 = !DILocation(line: 80, column: 11, scope: !168)
!221 = !DILocation(line: 80, column: 9, scope: !168)
!222 = !DILocation(line: 81, column: 11, scope: !168)
!223 = !DILocation(line: 81, column: 14, scope: !168)
!224 = !DILocation(line: 81, column: 9, scope: !168)
!225 = !DILocation(line: 82, column: 5, scope: !168)
!226 = !DILocation(line: 84, column: 7, scope: !163)
!227 = !DILocation(line: 51, column: 3, scope: !228)
!228 = !DILexicalBlockFile(scope: !77, file: !1, discriminator: 1)
!229 = !DILocation(line: 87, column: 15, scope: !6)
!230 = !DILocation(line: 87, column: 18, scope: !6)
!231 = !DILocation(line: 87, column: 3, scope: !6)
!232 = !DILocation(line: 87, column: 6, scope: !6)
!233 = !DILocation(line: 87, column: 13, scope: !6)
!234 = !DILocation(line: 88, column: 16, scope: !6)
!235 = !DILocation(line: 88, column: 19, scope: !6)
!236 = !DILocation(line: 88, column: 3, scope: !6)
!237 = !DILocation(line: 88, column: 6, scope: !6)
!238 = !DILocation(line: 88, column: 14, scope: !6)
!239 = !DILocation(line: 89, column: 18, scope: !6)
!240 = !DILocation(line: 89, column: 3, scope: !6)
!241 = !DILocation(line: 89, column: 6, scope: !6)
!242 = !DILocation(line: 89, column: 14, scope: !6)
!243 = !DILocation(line: 90, column: 17, scope: !6)
!244 = !DILocation(line: 90, column: 3, scope: !6)
!245 = !DILocation(line: 90, column: 6, scope: !6)
!246 = !DILocation(line: 90, column: 13, scope: !6)
!247 = !DILocation(line: 92, column: 10, scope: !6)
!248 = !DILocation(line: 92, column: 3, scope: !6)
!249 = !DILocation(line: 93, column: 1, scope: !6)
!250 = !DILocalVariable(name: "i", arg: 1, scope: !28, file: !1, line: 100, type: !18)
!251 = !DILocation(line: 100, column: 51, scope: !28)
!252 = !DILocalVariable(name: "t", arg: 2, scope: !28, file: !1, line: 101, type: !9)
!253 = !DILocation(line: 101, column: 54, scope: !28)
!254 = !DILocalVariable(name: "node", arg: 3, scope: !28, file: !1, line: 102, type: !9)
!255 = !DILocation(line: 102, column: 54, scope: !28)
!256 = !DILocation(line: 106, column: 6, scope: !257)
!257 = distinct !DILexicalBlock(scope: !28, file: !1, line: 106, column: 6)
!258 = !DILocation(line: 106, column: 11, scope: !257)
!259 = !DILocation(line: 106, column: 6, scope: !28)
!260 = !DILocation(line: 107, column: 12, scope: !257)
!261 = !DILocation(line: 107, column: 5, scope: !257)
!262 = !DILocation(line: 109, column: 6, scope: !263)
!263 = distinct !DILexicalBlock(scope: !28, file: !1, line: 109, column: 6)
!264 = !DILocation(line: 109, column: 8, scope: !263)
!265 = !DILocation(line: 109, column: 6, scope: !28)
!266 = !DILocation(line: 110, column: 23, scope: !267)
!267 = distinct !DILexicalBlock(scope: !263, file: !1, line: 109, column: 17)
!268 = !DILocation(line: 110, column: 9, scope: !267)
!269 = !DILocation(line: 110, column: 7, scope: !267)
!270 = !DILocation(line: 111, column: 8, scope: !271)
!271 = distinct !DILexicalBlock(scope: !267, file: !1, line: 111, column: 8)
!272 = !DILocation(line: 111, column: 8, scope: !273)
!273 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 1)
!274 = !DILocation(line: 111, column: 8, scope: !275)
!275 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 2)
!276 = !DILocation(line: 111, column: 8, scope: !277)
!277 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 3)
!278 = !DILocation(line: 111, column: 8, scope: !279)
!279 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 4)
!280 = !DILocation(line: 111, column: 8, scope: !281)
!281 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 5)
!282 = !DILocation(line: 111, column: 8, scope: !283)
!283 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 6)
!284 = !DILocation(line: 111, column: 8, scope: !285)
!285 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 7)
!286 = !DILocation(line: 111, column: 8, scope: !287)
!287 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 8)
!288 = !DILocation(line: 111, column: 8, scope: !289)
!289 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 9)
!290 = !DILocation(line: 111, column: 26, scope: !289)
!291 = !DILocation(line: 116, column: 7, scope: !292)
!292 = distinct !DILexicalBlock(scope: !271, file: !1, line: 111, column: 31)
!293 = !DILocation(line: 116, column: 13, scope: !292)
!294 = !DILocation(line: 116, column: 19, scope: !292)
!295 = !DILocation(line: 118, column: 21, scope: !292)
!296 = !DILocation(line: 118, column: 7, scope: !292)
!297 = !DILocation(line: 118, column: 13, scope: !292)
!298 = !DILocation(line: 118, column: 19, scope: !292)
!299 = !DILocation(line: 119, column: 21, scope: !292)
!300 = !DILocation(line: 119, column: 24, scope: !292)
!301 = !DILocation(line: 119, column: 7, scope: !292)
!302 = !DILocation(line: 119, column: 13, scope: !292)
!303 = !DILocation(line: 119, column: 19, scope: !292)
!304 = !DILocation(line: 120, column: 25, scope: !292)
!305 = !DILocation(line: 120, column: 7, scope: !292)
!306 = !DILocation(line: 120, column: 10, scope: !292)
!307 = !DILocation(line: 120, column: 17, scope: !292)
!308 = !DILocation(line: 120, column: 23, scope: !292)
!309 = !DILocation(line: 121, column: 18, scope: !292)
!310 = !DILocation(line: 121, column: 7, scope: !292)
!311 = !DILocation(line: 121, column: 10, scope: !292)
!312 = !DILocation(line: 121, column: 16, scope: !292)
!313 = !DILocation(line: 123, column: 14, scope: !292)
!314 = !DILocation(line: 123, column: 7, scope: !292)
!315 = !DILocation(line: 125, column: 3, scope: !267)
!316 = !DILocation(line: 127, column: 6, scope: !317)
!317 = distinct !DILexicalBlock(scope: !28, file: !1, line: 127, column: 6)
!318 = !DILocation(line: 127, column: 8, scope: !317)
!319 = !DILocation(line: 127, column: 6, scope: !28)
!320 = !DILocation(line: 128, column: 21, scope: !321)
!321 = distinct !DILexicalBlock(scope: !317, file: !1, line: 127, column: 17)
!322 = !DILocation(line: 128, column: 27, scope: !321)
!323 = !DILocation(line: 128, column: 34, scope: !321)
!324 = !DILocation(line: 128, column: 5, scope: !321)
!325 = !DILocation(line: 128, column: 11, scope: !321)
!326 = !DILocation(line: 128, column: 19, scope: !321)
!327 = !DILocation(line: 129, column: 3, scope: !321)
!328 = !DILocation(line: 130, column: 11, scope: !329)
!329 = distinct !DILexicalBlock(scope: !317, file: !1, line: 130, column: 11)
!330 = !DILocation(line: 130, column: 11, scope: !331)
!331 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 1)
!332 = !DILocation(line: 130, column: 11, scope: !333)
!333 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 2)
!334 = !DILocation(line: 130, column: 11, scope: !335)
!335 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 3)
!336 = !DILocation(line: 130, column: 11, scope: !337)
!337 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 4)
!338 = !DILocation(line: 130, column: 11, scope: !339)
!339 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 5)
!340 = !DILocation(line: 130, column: 11, scope: !341)
!341 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 6)
!342 = !DILocation(line: 130, column: 11, scope: !343)
!343 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 7)
!344 = !DILocation(line: 130, column: 11, scope: !345)
!345 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 8)
!346 = !DILocation(line: 130, column: 11, scope: !347)
!347 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 9)
!348 = !DILocation(line: 130, column: 30, scope: !347)
!349 = !DILocation(line: 131, column: 21, scope: !350)
!350 = distinct !DILexicalBlock(scope: !329, file: !1, line: 130, column: 35)
!351 = !DILocation(line: 131, column: 24, scope: !350)
!352 = !DILocation(line: 131, column: 5, scope: !350)
!353 = !DILocation(line: 131, column: 11, scope: !350)
!354 = !DILocation(line: 131, column: 19, scope: !350)
!355 = !DILocation(line: 132, column: 20, scope: !350)
!356 = !DILocation(line: 132, column: 5, scope: !350)
!357 = !DILocation(line: 132, column: 11, scope: !350)
!358 = !DILocation(line: 132, column: 18, scope: !350)
!359 = !DILocation(line: 133, column: 5, scope: !350)
!360 = !DILocation(line: 133, column: 8, scope: !350)
!361 = !DILocation(line: 133, column: 16, scope: !350)
!362 = !DILocation(line: 135, column: 3, scope: !350)
!363 = !DILocation(line: 137, column: 20, scope: !364)
!364 = distinct !DILexicalBlock(scope: !329, file: !1, line: 136, column: 8)
!365 = !DILocation(line: 137, column: 23, scope: !364)
!366 = !DILocation(line: 137, column: 5, scope: !364)
!367 = !DILocation(line: 137, column: 11, scope: !364)
!368 = !DILocation(line: 137, column: 18, scope: !364)
!369 = !DILocation(line: 138, column: 21, scope: !364)
!370 = !DILocation(line: 138, column: 5, scope: !364)
!371 = !DILocation(line: 138, column: 11, scope: !364)
!372 = !DILocation(line: 138, column: 19, scope: !364)
!373 = !DILocation(line: 139, column: 5, scope: !364)
!374 = !DILocation(line: 139, column: 8, scope: !364)
!375 = !DILocation(line: 139, column: 15, scope: !364)
!376 = !DILocation(line: 141, column: 3, scope: !28)
!377 = !DILocation(line: 141, column: 9, scope: !28)
!378 = !DILocation(line: 141, column: 15, scope: !28)
!379 = !DILocation(line: 144, column: 17, scope: !28)
!380 = !DILocation(line: 144, column: 3, scope: !28)
!381 = !DILocation(line: 144, column: 9, scope: !28)
!382 = !DILocation(line: 144, column: 15, scope: !28)
!383 = !DILocation(line: 145, column: 17, scope: !28)
!384 = !DILocation(line: 145, column: 3, scope: !28)
!385 = !DILocation(line: 145, column: 9, scope: !28)
!386 = !DILocation(line: 145, column: 15, scope: !28)
!387 = !DILocation(line: 146, column: 10, scope: !28)
!388 = !DILocation(line: 146, column: 3, scope: !28)
!389 = !DILocation(line: 147, column: 1, scope: !28)
!390 = !DILocalVariable(name: "i", arg: 1, scope: !31, file: !1, line: 152, type: !18)
!391 = !DILocation(line: 152, column: 52, scope: !31)
!392 = !DILocalVariable(name: "t", arg: 2, scope: !31, file: !1, line: 153, type: !9)
!393 = !DILocation(line: 153, column: 58, scope: !31)
!394 = !DILocalVariable(name: "removed", arg: 3, scope: !31, file: !1, line: 154, type: !34)
!395 = !DILocation(line: 154, column: 59, scope: !31)
!396 = !DILocalVariable(name: "x", scope: !31, file: !1, line: 157, type: !9)
!397 = !DILocation(line: 157, column: 21, scope: !31)
!398 = !DILocation(line: 159, column: 7, scope: !399)
!399 = distinct !DILexicalBlock(scope: !31, file: !1, line: 159, column: 6)
!400 = !DILocation(line: 159, column: 6, scope: !31)
!401 = !DILocation(line: 160, column: 6, scope: !402)
!402 = distinct !DILexicalBlock(scope: !399, file: !1, line: 159, column: 10)
!403 = !DILocation(line: 160, column: 14, scope: !402)
!404 = !DILocation(line: 161, column: 5, scope: !402)
!405 = !DILocation(line: 165, column: 27, scope: !31)
!406 = !DILocation(line: 165, column: 7, scope: !31)
!407 = !DILocation(line: 165, column: 5, scope: !31)
!408 = !DILocation(line: 166, column: 6, scope: !409)
!409 = distinct !DILexicalBlock(scope: !31, file: !1, line: 166, column: 6)
!410 = !DILocation(line: 166, column: 6, scope: !411)
!411 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 1)
!412 = !DILocation(line: 166, column: 6, scope: !413)
!413 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 2)
!414 = !DILocation(line: 166, column: 6, scope: !415)
!415 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 3)
!416 = !DILocation(line: 166, column: 6, scope: !417)
!417 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 4)
!418 = !DILocation(line: 166, column: 6, scope: !419)
!419 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 5)
!420 = !DILocation(line: 166, column: 6, scope: !421)
!421 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 6)
!422 = !DILocation(line: 166, column: 6, scope: !423)
!423 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 7)
!424 = !DILocation(line: 166, column: 6, scope: !425)
!425 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 8)
!426 = !DILocation(line: 166, column: 6, scope: !427)
!427 = !DILexicalBlockFile(scope: !409, file: !1, discriminator: 9)
!428 = !DILocation(line: 166, column: 25, scope: !427)
!429 = !DILocation(line: 168, column: 6, scope: !430)
!430 = distinct !DILexicalBlock(scope: !409, file: !1, line: 166, column: 30)
!431 = !DILocation(line: 168, column: 14, scope: !430)
!432 = !DILocation(line: 169, column: 12, scope: !430)
!433 = !DILocation(line: 169, column: 5, scope: !430)
!434 = !DILocation(line: 173, column: 7, scope: !31)
!435 = !DILocation(line: 173, column: 10, scope: !31)
!436 = !DILocation(line: 173, column: 5, scope: !31)
!437 = !DILocation(line: 174, column: 6, scope: !438)
!438 = distinct !DILexicalBlock(scope: !31, file: !1, line: 174, column: 6)
!439 = !DILocation(line: 174, column: 11, scope: !438)
!440 = !DILocation(line: 174, column: 8, scope: !438)
!441 = !DILocation(line: 174, column: 6, scope: !31)
!442 = !DILocation(line: 179, column: 5, scope: !443)
!443 = distinct !DILexicalBlock(scope: !438, file: !1, line: 174, column: 14)
!444 = !DILocation(line: 179, column: 8, scope: !443)
!445 = !DILocation(line: 179, column: 14, scope: !443)
!446 = !DILocation(line: 179, column: 17, scope: !443)
!447 = !DILocation(line: 180, column: 17, scope: !443)
!448 = !DILocation(line: 180, column: 20, scope: !443)
!449 = !DILocation(line: 180, column: 5, scope: !443)
!450 = !DILocation(line: 180, column: 8, scope: !443)
!451 = !DILocation(line: 180, column: 15, scope: !443)
!452 = !DILocation(line: 181, column: 18, scope: !443)
!453 = !DILocation(line: 181, column: 21, scope: !443)
!454 = !DILocation(line: 181, column: 5, scope: !443)
!455 = !DILocation(line: 181, column: 8, scope: !443)
!456 = !DILocation(line: 181, column: 16, scope: !443)
!457 = !DILocation(line: 182, column: 16, scope: !443)
!458 = !DILocation(line: 182, column: 19, scope: !443)
!459 = !DILocation(line: 182, column: 5, scope: !443)
!460 = !DILocation(line: 182, column: 8, scope: !443)
!461 = !DILocation(line: 182, column: 14, scope: !443)
!462 = !DILocation(line: 183, column: 23, scope: !443)
!463 = !DILocation(line: 183, column: 5, scope: !443)
!464 = !DILocation(line: 183, column: 8, scope: !443)
!465 = !DILocation(line: 183, column: 15, scope: !443)
!466 = !DILocation(line: 183, column: 21, scope: !443)
!467 = !DILocation(line: 185, column: 16, scope: !443)
!468 = !DILocation(line: 185, column: 6, scope: !443)
!469 = !DILocation(line: 185, column: 14, scope: !443)
!470 = !DILocation(line: 186, column: 12, scope: !443)
!471 = !DILocation(line: 186, column: 5, scope: !443)
!472 = !DILocation(line: 190, column: 7, scope: !31)
!473 = !DILocation(line: 190, column: 10, scope: !31)
!474 = !DILocation(line: 190, column: 5, scope: !31)
!475 = !DILocation(line: 191, column: 14, scope: !31)
!476 = !DILocation(line: 191, column: 4, scope: !31)
!477 = !DILocation(line: 191, column: 12, scope: !31)
!478 = !DILocation(line: 193, column: 10, scope: !31)
!479 = !DILocation(line: 193, column: 3, scope: !31)
!480 = !DILocation(line: 194, column: 1, scope: !31)
!481 = !DILocalVariable(name: "t", arg: 1, scope: !35, file: !1, line: 208, type: !9)
!482 = !DILocation(line: 208, column: 46, scope: !35)
!483 = !DILocalVariable(name: "removenode", arg: 2, scope: !35, file: !1, line: 209, type: !9)
!484 = !DILocation(line: 209, column: 46, scope: !35)
!485 = !DILocalVariable(name: "newroot", arg: 3, scope: !35, file: !1, line: 210, type: !34)
!486 = !DILocation(line: 210, column: 47, scope: !35)
!487 = !DILocalVariable(name: "x", scope: !35, file: !1, line: 213, type: !9)
!488 = !DILocation(line: 213, column: 21, scope: !35)
!489 = !DILocation(line: 215, column: 7, scope: !490)
!490 = distinct !DILexicalBlock(scope: !35, file: !1, line: 215, column: 6)
!491 = !DILocation(line: 215, column: 9, scope: !490)
!492 = !DILocation(line: 215, column: 13, scope: !493)
!493 = !DILexicalBlockFile(scope: !490, file: !1, discriminator: 1)
!494 = !DILocation(line: 215, column: 6, scope: !493)
!495 = !DILocation(line: 216, column: 5, scope: !490)
!496 = !DILocation(line: 218, column: 6, scope: !497)
!497 = distinct !DILexicalBlock(scope: !35, file: !1, line: 218, column: 6)
!498 = !DILocation(line: 218, column: 6, scope: !499)
!499 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 1)
!500 = !DILocation(line: 218, column: 6, scope: !501)
!501 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 2)
!502 = !DILocation(line: 218, column: 6, scope: !503)
!503 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 3)
!504 = !DILocation(line: 218, column: 6, scope: !505)
!505 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 4)
!506 = !DILocation(line: 218, column: 6, scope: !507)
!507 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 5)
!508 = !DILocation(line: 218, column: 6, scope: !509)
!509 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 6)
!510 = !DILocation(line: 218, column: 6, scope: !511)
!511 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 7)
!512 = !DILocation(line: 218, column: 6, scope: !513)
!513 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 8)
!514 = !DILocation(line: 218, column: 6, scope: !515)
!515 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 9)
!516 = !DILocation(line: 218, column: 44, scope: !515)
!517 = !DILocation(line: 221, column: 8, scope: !518)
!518 = distinct !DILexicalBlock(scope: !519, file: !1, line: 221, column: 8)
!519 = distinct !DILexicalBlock(scope: !497, file: !1, line: 218, column: 50)
!520 = !DILocation(line: 221, column: 20, scope: !518)
!521 = !DILocation(line: 221, column: 29, scope: !518)
!522 = !DILocation(line: 221, column: 26, scope: !518)
!523 = !DILocation(line: 221, column: 8, scope: !519)
!524 = !DILocation(line: 223, column: 7, scope: !518)
!525 = !DILocation(line: 225, column: 32, scope: !519)
!526 = !DILocation(line: 225, column: 44, scope: !519)
!527 = !DILocation(line: 225, column: 5, scope: !519)
!528 = !DILocation(line: 225, column: 17, scope: !519)
!529 = !DILocation(line: 225, column: 24, scope: !519)
!530 = !DILocation(line: 225, column: 30, scope: !519)
!531 = !DILocation(line: 226, column: 32, scope: !519)
!532 = !DILocation(line: 226, column: 44, scope: !519)
!533 = !DILocation(line: 226, column: 5, scope: !519)
!534 = !DILocation(line: 226, column: 17, scope: !519)
!535 = !DILocation(line: 226, column: 24, scope: !519)
!536 = !DILocation(line: 226, column: 30, scope: !519)
!537 = !DILocation(line: 229, column: 25, scope: !519)
!538 = !DILocation(line: 229, column: 5, scope: !519)
!539 = !DILocation(line: 229, column: 17, scope: !519)
!540 = !DILocation(line: 229, column: 23, scope: !519)
!541 = !DILocation(line: 231, column: 16, scope: !519)
!542 = !DILocation(line: 231, column: 6, scope: !519)
!543 = !DILocation(line: 231, column: 14, scope: !519)
!544 = !DILocation(line: 232, column: 5, scope: !519)
!545 = !DILocation(line: 235, column: 18, scope: !35)
!546 = !DILocation(line: 235, column: 30, scope: !35)
!547 = !DILocation(line: 235, column: 35, scope: !35)
!548 = !DILocation(line: 235, column: 7, scope: !35)
!549 = !DILocation(line: 235, column: 5, scope: !35)
!550 = !DILocation(line: 244, column: 6, scope: !551)
!551 = distinct !DILexicalBlock(scope: !35, file: !1, line: 244, column: 6)
!552 = !DILocation(line: 244, column: 11, scope: !551)
!553 = !DILocation(line: 244, column: 8, scope: !551)
!554 = !DILocation(line: 244, column: 6, scope: !35)
!555 = !DILocation(line: 245, column: 5, scope: !551)
!556 = !DILocation(line: 249, column: 7, scope: !35)
!557 = !DILocation(line: 249, column: 10, scope: !35)
!558 = !DILocation(line: 249, column: 5, scope: !35)
!559 = !DILocation(line: 250, column: 6, scope: !560)
!560 = distinct !DILexicalBlock(scope: !35, file: !1, line: 250, column: 6)
!561 = !DILocation(line: 250, column: 11, scope: !560)
!562 = !DILocation(line: 250, column: 8, scope: !560)
!563 = !DILocation(line: 250, column: 6, scope: !35)
!564 = !DILocation(line: 254, column: 5, scope: !565)
!565 = distinct !DILexicalBlock(scope: !560, file: !1, line: 250, column: 14)
!566 = !DILocation(line: 254, column: 8, scope: !565)
!567 = !DILocation(line: 254, column: 14, scope: !565)
!568 = !DILocation(line: 254, column: 17, scope: !565)
!569 = !DILocation(line: 255, column: 17, scope: !565)
!570 = !DILocation(line: 255, column: 20, scope: !565)
!571 = !DILocation(line: 255, column: 5, scope: !565)
!572 = !DILocation(line: 255, column: 8, scope: !565)
!573 = !DILocation(line: 255, column: 15, scope: !565)
!574 = !DILocation(line: 256, column: 18, scope: !565)
!575 = !DILocation(line: 256, column: 21, scope: !565)
!576 = !DILocation(line: 256, column: 5, scope: !565)
!577 = !DILocation(line: 256, column: 8, scope: !565)
!578 = !DILocation(line: 256, column: 16, scope: !565)
!579 = !DILocation(line: 257, column: 16, scope: !565)
!580 = !DILocation(line: 257, column: 19, scope: !565)
!581 = !DILocation(line: 257, column: 5, scope: !565)
!582 = !DILocation(line: 257, column: 8, scope: !565)
!583 = !DILocation(line: 257, column: 14, scope: !565)
!584 = !DILocation(line: 258, column: 23, scope: !565)
!585 = !DILocation(line: 258, column: 5, scope: !565)
!586 = !DILocation(line: 258, column: 8, scope: !565)
!587 = !DILocation(line: 258, column: 15, scope: !565)
!588 = !DILocation(line: 258, column: 21, scope: !565)
!589 = !DILocation(line: 259, column: 3, scope: !565)
!590 = !DILocation(line: 262, column: 8, scope: !591)
!591 = distinct !DILexicalBlock(scope: !592, file: !1, line: 262, column: 8)
!592 = distinct !DILexicalBlock(scope: !560, file: !1, line: 260, column: 8)
!593 = !DILocation(line: 262, column: 11, scope: !591)
!594 = !DILocation(line: 262, column: 19, scope: !591)
!595 = !DILocation(line: 262, column: 8, scope: !592)
!596 = !DILocation(line: 263, column: 11, scope: !591)
!597 = !DILocation(line: 263, column: 14, scope: !591)
!598 = !DILocation(line: 263, column: 9, scope: !591)
!599 = !DILocation(line: 263, column: 7, scope: !591)
!600 = !DILocation(line: 265, column: 22, scope: !601)
!601 = distinct !DILexicalBlock(scope: !591, file: !1, line: 264, column: 10)
!602 = !DILocation(line: 265, column: 34, scope: !601)
!603 = !DILocation(line: 265, column: 39, scope: !601)
!604 = !DILocation(line: 265, column: 42, scope: !601)
!605 = !DILocation(line: 265, column: 11, scope: !601)
!606 = !DILocation(line: 265, column: 9, scope: !601)
!607 = !DILocation(line: 266, column: 19, scope: !601)
!608 = !DILocation(line: 266, column: 22, scope: !601)
!609 = !DILocation(line: 266, column: 7, scope: !601)
!610 = !DILocation(line: 266, column: 10, scope: !601)
!611 = !DILocation(line: 266, column: 17, scope: !601)
!612 = !DILocation(line: 270, column: 14, scope: !35)
!613 = !DILocation(line: 270, column: 4, scope: !35)
!614 = !DILocation(line: 270, column: 12, scope: !35)
!615 = !DILocation(line: 272, column: 3, scope: !35)
!616 = !DILocation(line: 273, column: 1, scope: !35)
